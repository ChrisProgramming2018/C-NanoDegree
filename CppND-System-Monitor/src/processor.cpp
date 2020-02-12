#include "processor.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  // compute the percent of 
  
  cpus = cpus + 0.1;
  if (cpus >= 1) {cpus = 0;}


  return cpus; 
}


Processor::Processor() {
  cpus = 0.0;
}
