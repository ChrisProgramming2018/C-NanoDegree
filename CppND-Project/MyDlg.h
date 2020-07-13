/*
 * =====================================================================================
 *
 *       Filename:  MyDlg.h
 *
 *    Description:  This dialog will demonstrate the use of QFormLayout and the way
 *                  to combine multiple layouts in the same dialog.
 *                  It will also given an idea on how to make use of QLabel, QLineEdit
 *                  and QPushButton and Signals and Slots.
 *
 *        Version:  1.0
 *        Created:  10/22/2016
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jeganathan Swaminathan <jegan@tektutor.org>
 *   Organization:  TekTutor <www.tektutor.org>
 *
 * =====================================================================================
 */

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
  QPushButton *pAddButton, *pFirstWordButton, *pSecWordButton, *pExitButton;
  QRect *rec;
 public:
  QTimer *timer;
  MyDlg();
  ~MyDlg();
 private slots:
 void onAddButtonClicked();
 void onFirstWordButtonClicked();
 void onSecWordBottonClicked();
 void onExitButtonClicked();
 void showTime();
};
