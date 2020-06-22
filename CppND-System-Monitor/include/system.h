#ifndef SYSTEM_H
#define SYSTEM_H

#include <getopt.h>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  void updateCpuUtilization();
  Processor& Cpu(int number);                   // TODO: See src/system.cpp
  std::vector<Process>& Processes();  // TODO: See src/system.cpp
  float MemoryUtilization();          // TODO: See src/system.cpp
  std::string UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               // TODO: See src/system.cpp
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();               // TODO: See src/system.cpp
  std::string OperatingSystem();
  int _amountCores;
  long int _upTime;
  void parseCommandLineArguments(int argc, char** argv);
  int getShowProcesses();
  std::string _sortBy;                      // TODO: See src/system.cpp
  std::string getSortBy();
 private:
  // void  computeTime(Processor &pro, std::string line);
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::vector<Processor> _listOfCores = {};
  int _amountProcessesShow; 
};

#endif
