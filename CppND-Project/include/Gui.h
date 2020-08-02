// Copyright 2020
// cpp course
// Author: Christian Leininger <info2016frei@gmail.com>

#ifndef CPPND_PROJECT_INCLUDE_GUI_H_
#define CPPND_PROJECT_INCLUDE_GUI_H_



#include <glob.h>
#include <QLabel>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <string>
#include <vector>
#include <ctime>
#include <iostream>

#include "LSTModel.h"

class WorkerThread : public QThread {
 public:
  WorkerThread();
  LSTMModel *_model;
  bool _break;
  bool _loadModel;
  void run();
};

class MyDlg : public QWidget {
 public:
  QTimer *timer, *timer2;
  explicit MyDlg();
  virtual ~MyDlg() {}
  void predict();
  void setPath();
  std::string _word1;
  Q_OBJECT

 private:
  QVBoxLayout *pMainLayout;
  QBoxLayout *pButtonLayout;
  QFormLayout *pFormLayout;
  QComboBox *_comboBox;
  WorkerThread *_workerThread;
  QLineEdit *pFirstEdit, *pWord1Edit, *pWord2Edit, *pWord3Edit, *pWord4Edit;
  QLineEdit *pResultEdit, *pTimeEdit;
  QString _wordInput, _predictWord1, _predictWord2, _predictWord3, _predictWord4;
  QLabel *pFirstLabel, *pSecondLabel, *pThirdLabel, *pFourthLabel, *pResultLabel;
  QLabel *pTimeLabel, *pLoadModelLabel, *pDataPathlLabel;
  QPushButton *pLoadModelButton, *pPredictButton, *pFirstWordButton, *pSecWordButton;
  QPushButton *pThirdWordButton, *pFourthWordButton, *pExitButton;
  QRect *rec;
  std::string _path;
  std::vector<std::string> globVector(const std::string& pattern);
  std::string get_current_dir();
  std::vector<std::string> _files;

 private slots:
  void onPredictButtonClicked();
  void onLoadModelButtonClicked();
  void onFirstWordButtonClicked();
  void onSecWordBottonClicked();
  void onThirdWordBottonClicked();
  void onFourthWordBottonClicked();
  void onExitButtonClicked();
  void showTime();
};

#endif  // CPPND_PROJECT_INCLUDE_GUI_H_
