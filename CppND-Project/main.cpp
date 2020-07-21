#include <QApplication>
#include "MyDlg.h"
#include <iostream>
int main (int argc, char **argv) {
  QApplication theApp(argc,argv);
  MyDlg dlg;
  dlg.show();
  return theApp.exec();
}
