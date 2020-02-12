#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;


System::System() {
  _amountCores = LinuxParser::CpuUtilization().size();
}


// TODO: Return the system's CPU
Processor& System::Cpu() {
  vector<string> cpuLines = LinuxParser::CpuUtilization();
  for (int i = 0; i <= cpuLines.size(); i++) {
    // std::cout << cpuLines[i] << std::endl;
  }
  return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  return processes_; 
}

// Return the system's kernel identifier (string)
std::string System::Kernel() { 
  return LinuxParser::Kernel(); 
}

// Return the system's memory utilization
float System::MemoryUtilization() { 
  return LinuxParser::MemoryUtilization(); 
}

// Return the operating system name
std::string System::OperatingSystem() { 
  return LinuxParser::OperatingSystem(); 
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// Return the total number of processes on the system
int System::TotalProcesses() { 
  return LinuxParser::TotalProcesses(); 
}

// Return the number of seconds since the system started running
string System::UpTime() { 
  string currentTime = "";
  long int time = LinuxParser::UpTime();
  int hour = time / 3600;
  int min = (time / 60) % 60 ;
  int sec = time % 60;
  string pre_hour = "";
  string pre_min = "";
  string pre_sec = "";
  if (sec < 10) { pre_sec = "0";}
  if (min < 10) {pre_min = "0";}
  if (hour < 10){ pre_hour = "0";}

  return  pre_hour + std::to_string(hour) + ":" + pre_min + std::to_string(min) + ":" + pre_sec + std::to_string(sec);
}
