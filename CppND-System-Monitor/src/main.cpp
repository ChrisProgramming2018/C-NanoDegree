#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  // system.Kernel();
  // system.MemoryUtilization();
  // system.TotalProcesses();
  NCursesDisplay::Display(system);
}
