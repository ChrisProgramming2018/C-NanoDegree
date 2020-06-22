#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int pid, std::string sortBy);
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp
  void setRam(std::string value);
  std::string getRam();
  void setCommand(std::string name);
  std::string getCommand();
  void setUpTime(long int time);
  long int getUpTime();
  void setCpuUtilization(float cpu); 
  void setUserName(std::string name);
  void setUid(int uid);
  int getUid(); 
  
  int _pid;
  std::string _ram;
  std::string _command;
  std::string _userName;
  std::string _sortBy;
  int _uid;  
  long int _upTime;
  long int _seconds;
  long int _totalTime;
  float  _cpu;
 private:
};

#endif
