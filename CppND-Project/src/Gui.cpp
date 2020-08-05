// Copyright 2020
// cpp project
// Author: Christian Leininger <info2016frei@gmail.com>


#include <unistd.h>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QColorDialog>
#include <QAction>
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include "../include/Gui.h"
using namespace std::chrono_literals;


// ________________________________________________________________________________________________
WorkerThread::WorkerThread() {
  _model = new LSTMModel();
  _loadModel = false;
  _break = false;
}

// ________________________________________________________________________________________________
void WorkerThread::run() {
  std::cout << "wait for load model" << std::endl;
  while (!_loadModel) {
    std::this_thread::sleep_for(2s);
  }
  _model->loadModel();
}


// ________________________________________________________________________________________________
MyDlg::MyDlg() {
  this->setFixedSize(1600, 800);
  this->setStyleSheet("background-color:white;");
  _word1 = " ";
  pLoadModelButton = new QPushButton("Load Model");
  pPredictButton = new QPushButton("Predict");
  pFirstWordButton = new QPushButton("First Word");
  pSecWordButton = new QPushButton("Sec Word");
  pThirdWordButton = new QPushButton("Third Word");
  pFourthWordButton = new QPushButton("Fourth Word");
  pExitButton = new QPushButton("Exit");

  // DropBox
  _path = get_current_dir();
  _path.append("/../data/*");

  _comboBox = new QComboBox();
  std::string words;
  std::vector<std::string> _files = globVector(_path);
  for (size_t i = 0; i < _files.size(); i++) {
    _comboBox->addItem(tr(_files[i].c_str()));
  }
  // set shortcuts
  QAction* pAction = new QAction("text4ESC", this);
  pAction->setShortcut(Qt::Key_Escape);
  pAction->setShortcutContext(Qt::WindowShortcut);
  connect(pAction, SIGNAL(triggered()), this, SLOT(onExitButtonClicked()));
  addAction(pAction);
  setContextMenuPolicy(Qt::ActionsContextMenu);

  QAction* pAction1 = new QAction("loadModel", this);
  pAction1->setShortcut(Qt::Key_L | Qt::CTRL);
  connect(pAction1, SIGNAL(triggered()), this, SLOT(onLoadModelButtonClicked()));
  addAction(pAction1);


  QAction* pAction2 = new QAction("predictModel", this);
  pAction2->setShortcut(Qt::Key_P | Qt::CTRL);
  connect(pAction2, SIGNAL(triggered()), this, SLOT(onPredictButtonClicked()));
  addAction(pAction2);

  // layout
  pButtonLayout = new QBoxLayout(QBoxLayout::RightToLeft);
  timer = new QTimer(this);
  pButtonLayout->addWidget(pExitButton);
  pButtonLayout->addWidget(pFourthWordButton);
  pButtonLayout->addWidget(pThirdWordButton);
  pButtonLayout->addWidget(pSecWordButton);
  pButtonLayout->addWidget(pFirstWordButton);
  pButtonLayout->addWidget(pPredictButton);
  pButtonLayout->addWidget(pLoadModelButton);
  pButtonLayout->addWidget(_comboBox);
  pButtonLayout->addStretch();
  QTimer *timer = new QTimer(this);
  pFormLayout = new QFormLayout();

  pFirstEdit  = new QLineEdit();
  pWord1Edit = new QLineEdit();
  pWord2Edit = new QLineEdit();
  pWord3Edit = new QLineEdit();
  pWord4Edit = new QLineEdit();

  pResultEdit = new QLineEdit();
  pTimeEdit =   new QLineEdit();

  pTimeLabel = new QLabel();
  pLoadModelLabel = new QLabel();
  pDataPathlLabel = new QLabel();

  QColor color = QColorDialog::standardColor(20);  // 24 > green
  QPalette palette = pLoadModelLabel->palette();
  palette.setColor(QPalette::Window, color);
  pLoadModelLabel->setPalette(palette);
  pLoadModelLabel->setText("false");
  pFormLayout->addRow("Current Time", pTimeLabel);
  pFormLayout->addRow("Enter your text", pFirstEdit);
  pFormLayout->addRow("predicted Word", pWord1Edit);
  pFormLayout->addRow("predicted Word", pWord2Edit);
  pFormLayout->addRow("predicted Word", pWord3Edit);
  pFormLayout->addRow("predicted Word", pWord4Edit);
  pFormLayout->addRow("Result", pResultEdit);
  pFormLayout->addRow("Model loaded", pLoadModelLabel);
  pFormLayout->addRow("Path textfile ", pDataPathlLabel);

  pMainLayout = new QVBoxLayout(this);
  rec = new QRect();
  rec->setWidth(45);
  rec->setHeight(50);
  pButtonLayout->setGeometry(*rec);
  pMainLayout->addLayout(pFormLayout);
  pMainLayout->addLayout(pButtonLayout);
  setLayout(pMainLayout);

  // buttons
  connect(pPredictButton, SIGNAL(clicked()), this, SLOT(onPredictButtonClicked()));
  connect(pLoadModelButton, SIGNAL(clicked()), this, SLOT(onLoadModelButtonClicked()));
  connect(pFirstWordButton, SIGNAL(clicked()), this, SLOT(onFirstWordButtonClicked()));
  connect(pSecWordButton, SIGNAL(clicked()), this, SLOT(onSecWordBottonClicked()));
  connect(pThirdWordButton, SIGNAL(clicked()), this, SLOT(onThirdWordBottonClicked()));
  connect(pFourthWordButton, SIGNAL(clicked()), this, SLOT(onFourthWordBottonClicked()));
  connect(pExitButton, SIGNAL(clicked()), this, SLOT(onExitButtonClicked()));
  connect(_comboBox, SIGNAL(currentIndexChanged(QString)), pDataPathlLabel, SLOT(setText(QString)));

  // timer for watch
  connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
  timer->start(100);
  _workerThread = new WorkerThread;
  connect(_workerThread, SIGNAL(finished()),
      _workerThread, SLOT(deleteLater()));
  _workerThread->start();
}


// ________________________________________________________________________________________________
void MyDlg::predict() {
  qDebug() << " Predict next word " << _wordInput << endl;
  if (_wordInput.toStdString().empty()) {
    qDebug() << " Empty Input" << endl;
    return;
  }
  // pass word to thread model
  qDebug() << " load  word to model " << _wordInput << endl;
  _workerThread->_model->_predictBool = true;
  _workerThread->_model->_wordToPredict = _wordInput.toStdString();
  // wait for results
  while (!_workerThread->_model->_donePredict) {
    // wait at most 1 sec
  }
  _workerThread->_model->_donePredict = false;
  qDebug() << " results "  << endl;
  _predictWord1 = QString::fromStdString(_workerThread->_model->_wordsPredicted[0]);
  _predictWord2 = QString::fromStdString(_workerThread->_model->_wordsPredicted[1]);
  _predictWord3 = QString::fromStdString(_workerThread->_model->_wordsPredicted[2]);
  _predictWord4 = QString::fromStdString(_workerThread->_model->_wordsPredicted[3]);
  pFirstWordButton->setText(_predictWord1);
  pSecWordButton->setText(_predictWord2);
  pThirdWordButton->setText(_predictWord3);
  pFourthWordButton->setText(_predictWord4);
  pWord1Edit->setText(_predictWord1);
  pWord2Edit->setText(_predictWord2);
  pWord3Edit->setText(_predictWord3);
  pWord4Edit->setText(_predictWord4);
  return;
}


// ________________________________________________________________________________________________
void MyDlg::showTime() {
  QTime time = QTime::currentTime();
  QString text = time.toString("hh:mm:ss");
  if ((time.second() % 2) == 0) {
    text[2] = ' ';
    text[5] = ' ';
  }
  pTimeLabel->setText(text);
}

// ________________________________________________________________________________________________
void MyDlg::onPredictButtonClicked() {
  qDebug() << "Clicke predict ..." << endl;
  _wordInput  = pFirstEdit->text();
  // check if model is loaded
  if (!_workerThread->_loadModel) {
    qDebug() << "Load model first" << endl;
    return;
  }
  predict();
}

// ________________________________________________________________________________________________
void MyDlg::onFirstWordButtonClicked() {
  qDebug() << "First word button clicked ..." << endl;
  pResultEdit->setText(_wordInput + " " + _predictWord1);
}

// ________________________________________________________________________________________________
void MyDlg::onSecWordBottonClicked() {
  qDebug() << "second button clicked ..." << endl;
  pResultEdit->setText(_wordInput + " " + _predictWord2);
}


// ________________________________________________________________________________________________
void MyDlg::onThirdWordBottonClicked() {
  qDebug() << "second button clicked ..." << endl;
  pResultEdit->setText(_wordInput + " " + _predictWord3);
}

// ________________________________________________________________________________________________
void MyDlg::onFourthWordBottonClicked() {
  qDebug() << "second button clicked ..." << endl;
  pResultEdit->setText(_wordInput + " " + _predictWord4);
}


// ________________________________________________________________________________________________
void MyDlg::onLoadModelButtonClicked() {
  qDebug() << "Load" << pDataPathlLabel->text() << endl;
  _workerThread->_model->setWordPath(pDataPathlLabel->text().toStdString());
  _workerThread->_loadModel = true;

  qDebug() << "load model" << endl;
  pLoadModelLabel->setText("true");
}

// ________________________________________________________________________________________________
void MyDlg::onExitButtonClicked() {
  qDebug() << "Exit programm ..." << endl;
  exit(0);
}


// ______________________________________________________________
std::string MyDlg::get_current_dir() {
  char buff[FILENAME_MAX];  // create string buffer to hold path
  getcwd(buff, FILENAME_MAX);
  std::string current_working_dir(buff);
  return current_working_dir;
}


// ______________________________________________________________
std::vector<std::string> MyDlg::globVector(const std::string& pattern) {
  glob_t glob_result;
  glob(pattern.c_str(), GLOB_TILDE, NULL, &glob_result);
  std::vector<std::string> files;
  for (unsigned int i = 0; i < glob_result.gl_pathc; ++i) {
    files.push_back(std::string(glob_result.gl_pathv[i]));
  }
  globfree(&glob_result);
  return files;
}
