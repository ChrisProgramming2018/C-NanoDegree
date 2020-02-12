#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  // system.Kernel();
  // system.MemoryUtilization();
  //system.Cpu();
  NCursesDisplay::Display(system);
}
