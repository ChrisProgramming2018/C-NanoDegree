// Copyright 2020
// // Udacity Project
// // Author: Christian Leininger <info2016frei@gmail.com>


#include "../include/ncurses_display.h"
#include "../include/system.h"


int main(int argc, char** argv) {
  
  System system;
  system.parseCommandLineArguments(argc, argv);
  NCursesDisplay::Display(system);
}
