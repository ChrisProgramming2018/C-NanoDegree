#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp
  Processor();
  // Declare any necessary private members
 private:
  long long int _totalTimeOld;
  long long int _idleTimeOld;
  long long int _totalTimeNew;
  long long int _idleTimeNew;
  float cpus;
};

#endif
