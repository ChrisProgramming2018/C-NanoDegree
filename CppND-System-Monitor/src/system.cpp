// Copyright 2020
// // Udacity Project
// // Author: Christian Leininger <info2016frei@gmail.com>


#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include "../include/process.h"
#include "../include/format.h"
#include "../include/processor.h"
#include "../include/system.h"
#include "../include/linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// __________________________________________________________________________________________________________________________________________________
System::System() {
  _amountCores = LinuxParser::CpuUtilization().size();   // get amount of cores
  // create for each core a instance of processort
  for (int i = 0; i <= _amountCores; i++) {
    Processor p;
    _listOfCores.push_back(p);
  }
}


// __________________________________________________________________________________________________________________________________________________
void computeTime(Processor *pro, std::string line, bool old) {
  std::string name;
  std::string name1, name2, name3, name4, name5;
  std::string name6, name7, name8, name9, name10;

  std::istringstream linestream(line);
  linestream >> name >> name1 >>  name2 >>  name3 >> name4 >> name5 >>  name6 >>  name7 >> name8 >> name9 >> name10;
  pro->_name = name;
  int userTime = std::stoi(name1);
  int niceTime = std::stoi(name2);
  int systemTime = std::stoi(name3);
  int idleTime = std::stoi(name4);
  int ioWait = std::stoi(name5);
  int irq = std::stoi(name6);
  int softIrq = std::stoi(name7);
  int steal = std::stoi(name8);
  int guest = std::stoi(name9);
  int guestnice = std::stoi(name10);

  userTime = userTime - guest;
  niceTime = niceTime - guestnice;
  int idleallTime = idleTime + ioWait;
  int systemallTime = systemTime + irq + softIrq;
  int virtallTime = guest + guestnice;
  if (old) {
    pro->_idleallTimeOld = idleallTime;
    pro->_totalTimeOld = userTime + niceTime + systemallTime + idleallTime + steal + virtallTime;
    pro->_busyOld =  userTime + niceTime + systemallTime + steal + virtallTime;
  } else {
    pro->_idleallTimeNew = idleallTime;
    pro->_totalTimeNew = userTime + niceTime + systemallTime + idleallTime + steal + virtallTime;
    pro->_busyNew =  userTime + niceTime + systemallTime + steal + virtallTime;
  }
}



// _____________________________________________________________________________
void printUsageAndExit()  {
  std::cerr << "Usage: ./monitor\n";
  std::cerr << "Available options:\n";
  std::cerr << "--showProcesses <int> : Amount of how many Processes will be shown.\n";
  std::cerr << " (default: 10)\n";
  std::cerr << "--sortBy <string> : Sort by cpu memory time.\n";
  std::cerr << " (default: cpu)\n";
  exit(1);
}

// __________________________________________________________________________________________________________________________________________________
void System::parseCommandLineArguments(int argc, char** argv) {
   struct option options[] = {
     {"showProcesses", 1, NULL, 's'},
     {"sortBy", 1, NULL, 'b'},
     {NULL, 0, NULL, 0}
   };
   optind = 1;

   _amountProcessesShow = 10;
   _sortBy = "cpu";
   while (true) {
     char c = getopt_long(argc, argv, "s:", options, NULL);
     if (c == -1) { break; }
     switch (c) {
       case 's':
         _amountProcessesShow = atoi(optarg);
         break;
       case 'b':
         _sortBy = optarg;
         break;
       case 'h':
         printUsageAndExit();
         break;
       default:
         printUsageAndExit();
     }
   }
}


// __________________________________________________________________________________________________________________________________________________
void System::updateCpuUtilization() {
  vector<string> cpuLines = LinuxParser::CpuUtilization();
  for (int i = 0; i < static_cast<int>(cpuLines.size()); i++) {
    computeTime(&_listOfCores[i], cpuLines[i], true);
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  cpuLines = LinuxParser::CpuUtilization();
  for (int i = 0; i < static_cast<int>(cpuLines.size()); i++) {
    computeTime(&_listOfCores[i], cpuLines[i], false);
  }
  int totalTimeDiff;
  float idleallTimeDiff;
  for (int i = 0; i < static_cast<int>(cpuLines.size()); i++) {
    Processor *p = &_listOfCores[i];
    totalTimeDiff = p->_totalTimeNew - p->_totalTimeOld;
    idleallTimeDiff = p->_idleallTimeNew -p->_idleallTimeOld;
    p->_cpuUsage =(totalTimeDiff - idleallTimeDiff) / totalTimeDiff;
  }
}


// __________________________________________________________________________________________________________________________________________________
//  Return the system's CPU
Processor& System::Cpu(int number) {
  cpu_ = _listOfCores[number];
  return cpu_;
}

// __________________________________________________________________________________________________________________________________________________
//  Return a container composed of the system's processes
vector<Process>& System::Processes() {
  std::vector<int> pids =  LinuxParser::Pids();
  int number;
  processes_.clear();
  for (int i = 0; i < static_cast<int>(pids.size()); i++) {
    number = pids[i];
    Process p1(number, _sortBy);
    p1.setRam(LinuxParser::Ram(number));
    p1.setCommand(LinuxParser::Command(number));
    p1.setUpTime(LinuxParser::UpTime(number));
    p1.setCpuUtilization(LinuxParser::ProcessCpuUtilization(number));
    p1.setUserName(LinuxParser::User(number));
    p1.setUid(LinuxParser::Uid(number));
    p1.setUserName(LinuxParser::User(p1.getUid()));
    processes_.push_back(p1);
  }
  // sort vector after
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

// __________________________________________________________________________________________________________________________________________________
// Return the system's kernel identifier (string)
std::string System::Kernel() {
  return LinuxParser::Kernel();
}

// __________________________________________________________________________________________________________________________________________________
// Return the system's memory utilization
float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
}

// __________________________________________________________________________________________________________________________________________________
// Return the operating system name
std::string System::OperatingSystem() {
  return LinuxParser::OperatingSystem();
}

// __________________________________________________________________________________________________________________________________________________
// Return the number of processes actively running on the system
int System::RunningProcesses() {
  return  LinuxParser::RunningProcesses();
}

// __________________________t________________________________________________________________________________________________________________________
// Return the total number of processes on the system
int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

// __________________________________________________________________________________________________________________________________________________
// Return the number of seconds since the system started running
string System::UpTime() {
  string currentTime = "";
  int64_t  time = LinuxParser::UpTime();
  _upTime = time;
  return Format::ElapsedTime(time);
}

// __________________________________________________________________________________________________________________________________________________
int System::getShowProcesses() {
  return _amountProcessesShow;
}

// __________________________________________________________________________________________________________________________________________________
std::string System::getSortBy() {
  return _sortBy;
}
