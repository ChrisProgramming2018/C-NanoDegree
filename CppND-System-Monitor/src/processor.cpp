#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  // compute the percent of 
   
  // std::cout << "in side proccor " << _name << " usage "   << _cpuUsage << std::endl;

  return _cpuUsage; 
}


Processor::Processor() {
  cpus = 0.0;
}
