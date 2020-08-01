#include <QApplication>
#include "../include/MyDlg.h"
#include <iostream>

int main (int argc, char **argv) {
  std::cout << "Main programm " << std::endl;
   QApplication theApp(argc,argv);
  MyDlg dlg;
  dlg.show();
  return theApp.exec();
}
