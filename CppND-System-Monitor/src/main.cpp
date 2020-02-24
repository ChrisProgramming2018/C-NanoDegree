// Copyright 2020
// // Udacity Project
// // Author: Christian Leininger <info2016frei@gmail.com>


#include "../include/ncurses_display.h"
#include "../include/system.h"

int main() {
  System system;
  NCursesDisplay::Display(system, 40);
}
