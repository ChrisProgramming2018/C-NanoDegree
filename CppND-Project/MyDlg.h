#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QDialog>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QString>
#include <QDebug>
#include <string>
#include <ctime>

#include "helper.h"


class MyDlg : public QWidget {
  std::string _word1;
  Q_OBJECT
 private:
  QString _wordInput, _predictWord1, _predictWord2;
  QVBoxLayout *pMainLayout;
  QBoxLayout *pButtonLayout;
  QFormLayout *pFormLayout;
   
  QLineEdit *pFirstEdit, *pWord1Edit,*pWord2Edit, *pResultEdit, *pTimeEdit;
  QLabel *pFirstLabel, *pSecondLabel, *pResultLabel, *pTimeLabel;
  QPushButton *pLoadModelButton, *pAddButton, *pFirstWordButton, *pSecWordButton, *pExitButton;
  QRect *rec;
 public:
  QTimer *timer;
  MyDlg();
  ~MyDlg();
  LSTMModel *_model;
 private slots:
 void onAddButtonClicked();
 void onLoadModelButtonClicked();
 void onFirstWordButtonClicked();
 void onSecWordBottonClicked();
 void onExitButtonClicked();
 void showTime();
};
