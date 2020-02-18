#include "ncurses_display.h"
#include "system.h"

int main() {
  System system;
  // system.Kernel();
  // system.MemoryUtilization();
  // system.Cpu(1).Utilization();
  // std::cout << "Main " << std::endl;
  //while(true) {
    //system.updateCpuUtilization();
    // std::cout << "\r" << system.Cpu(1).Utilization() << std::flush;
    // std::cout << "\r" << system.Cpu(2).Utilization() << std::endl;
    // std::cout << "\r" << system.Cpu(2).Utilization() << std::endl;
    // std::cout << "\r" << system.Cpu(3).Utilization() << std::endl;
    // std::cout << "\r" << system.Cpu(4).Utilization() << std::endl;
    // std::cout << "\r" << system.Cpu(5).Utilization() << std::endl;
    // std::cout << "\r" << system.Cpu(6).Utilization() << std::endl;
    // std::cout << "\r" << system.Cpu(7).Utilization() << std::endl;
  //}
  // system.Processes();
  NCursesDisplay::Display(system, 40);
}
