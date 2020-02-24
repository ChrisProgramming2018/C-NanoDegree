// Copyright 2020
// // Udacity Project
// // Author: Christian Leininger <info2016frei@gmail.com>

#include "../include/processor.h"

//  Return the aggregate CPU utilization
// __________________________________________________________________________________________________________________________________________________
float Processor::Utilization() {
  // pase it to ncurses
  return _cpuUsage;
}

// __________________________________________________________________________________________________________________________________________________
Processor::Processor() {
  cpus = 0.0;
}
