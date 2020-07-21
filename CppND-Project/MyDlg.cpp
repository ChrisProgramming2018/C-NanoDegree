#include "MyDlg.h"
#include <QTime>
#include <QTimer>
#include <QThread>
#include <iostream>


MyDlg::MyDlg() {
  this->setFixedSize(1024, 800);
  _word1 = " "; 
  pAddButton = new QPushButton("Predict");
  pFirstWordButton = new QPushButton("First Word");
  pSecWordButton = new QPushButton("Sec Word");
  pExitButton = new QPushButton("Exit ");

  pButtonLayout = new QBoxLayout(QBoxLayout::RightToLeft);
  timer = new QTimer(this);
  pButtonLayout->addWidget ( pExitButton );
  pButtonLayout->addWidget ( pSecWordButton );
  pButtonLayout->addWidget ( pFirstWordButton );
  pButtonLayout->addWidget ( pAddButton );
  pButtonLayout->addStretch ( );
  QTimer *timer = new QTimer(this);
  pFormLayout = new QFormLayout();

  pFirstEdit  = new QLineEdit();
  pWord1Edit = new QLineEdit();
  pWord2Edit = new QLineEdit();
  pResultEdit = new QLineEdit();
  pTimeEdit =   new QLineEdit();
  
  pTimeLabel = new QLabel();
  pFormLayout->addRow("Current Time", pTimeLabel);
  pFormLayout->addRow("Enter your text",pFirstEdit);
  pFormLayout->addRow("predicted Word",pWord1Edit);
  pFormLayout->addRow("predicted Word",pWord2Edit);
  pFormLayout->addRow("Result", pResultEdit);

  pMainLayout = new QVBoxLayout(this);
  rec = new QRect(); 
  rec->setWidth(45);
  rec->setHeight(50);
  pButtonLayout->setGeometry(*rec);
  pMainLayout->addLayout ( pFormLayout );
  pMainLayout->addLayout ( pButtonLayout );
  
  setLayout ( pMainLayout );
  
  connect (
      pAddButton,
      SIGNAL ( clicked() ),
      this,
      SLOT ( onAddButtonClicked() )
      );
  connect (
      pFirstWordButton,
      SIGNAL ( clicked() ),
      this,
      SLOT ( onFirstWordButtonClicked() )
      );
  connect (
      pSecWordButton,
      SIGNAL ( clicked() ),
      this,
      SLOT ( onSecWordBottonClicked())
      );
  connect (
      pExitButton,
      SIGNAL ( clicked() ),
      this,
      SLOT ( onExitButtonClicked() )
      );
  connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
  timer->start(100);
}
MyDlg::~MyDlg() {
}

void MyDlg::showTime() {
  QTime time = QTime::currentTime();
  QString text = time.toString("hh:mm:ss");
  if ((time.second() % 2) == 0) {
    text[2] = ' ';
    text[5] = ' ';
  }
  pTimeLabel->setText(text);
}  
void MyDlg::onAddButtonClicked() {
  qDebug() << "Clicke predict ..." << endl;
  _wordInput  = pFirstEdit->text();
  _predictWord1 = " world 1 ";
  _predictWord2 = " world 2 ";
  pFirstWordButton->setText(_predictWord1);
  pWord1Edit->setText( _predictWord1 );
  pWord2Edit->setText( _predictWord2 );
}

void MyDlg::onFirstWordButtonClicked() {
  qDebug() << "First word button clicked ..." << endl;
  pResultEdit->setText( _wordInput + _predictWord1 );
}

void MyDlg::onSecWordBottonClicked() {
  qDebug() << "second button clicked ..." << endl;
  pResultEdit->setText( _wordInput + _predictWord2 );
}

void MyDlg::onExitButtonClicked() {
  qDebug() << "Exit programm ..." << endl;
  exit(0);
}
