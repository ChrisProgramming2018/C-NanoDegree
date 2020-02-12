#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <string>

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();
  std::string _name;
  int _idleallTimeOld;
  int _totalTimeOld;
  int _busyOld;
  int _idleallTimeNew;
  int _totalTimeNew;
  int _busyNew;
  float _cpuUsage;
  
  // Declare any necessary private members
 private:
  int _cpu;
  
  float cpus;
};

#endif
