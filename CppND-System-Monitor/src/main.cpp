#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  // system.Kernel();
  // system.MemoryUtilization();
  //system.Cpu(1).Utilization();
  std::cout << "Main " << std::endl;
  //std::cout << system.Cpu(1).Utilization() << std::endl;
  system.updateCpuUtilization();
  // NCursesDisplay::Display(system);
}
