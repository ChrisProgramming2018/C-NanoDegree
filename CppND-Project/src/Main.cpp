// Copyright 2020
// cpp Project
// Author: Christian Leininger <info2016frei@gmail.com>


#include <QApplication>
#include <iostream>
#include "../include/Gui.h"

int main(int argc, char **argv) {
  std::cout << "Main programm " << std::endl;
  QApplication theApp(argc, argv);
  MyDlg dlg;
  dlg.show();
  return theApp.exec();
}
