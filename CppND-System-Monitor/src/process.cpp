// Copyright 2020
// // Udacity Project
// // Author: Christian Leininger <info2016frei@gmail.com>



#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "../include/process.h"

using std::string;
using std::to_string;
using std::vector;

// ________________________________________________________________________________________________
Process::Process(int pid, std::string sortBy) {
  _pid = pid;
  _sortBy = sortBy;
}

// ________________________________________________________________________________________________
// Return this process's ID
int Process::Pid() {
  return _pid;
}


// ________________________________________________________________________________________________
void Process::setRam(std::string value) {
  _ram = value;
}

// ________________________________________________________________________________________________
std::string Process::getRam() {
  return _ram;
}

// ________________________________________________________________________________________________
void Process::setCommand(std::string name) {
  _command = name;
}

// ________________________________________________________________________________________________
std::string Process::getCommand() {
  return _command;
}

// ________________________________________________________________________________________________
void Process::setUpTime(int64_t time) {
  _upTime = time;
}

// ________________________________________________________________________________________________
int64_t Process::getUpTime() {
  return _upTime;
}

// ________________________________________________________________________________________________
void Process::setUserName(std::string name) {
  _userName = name;
}

// ________________________________________________________________________________________________
// Return this process's CPU utilization
float Process::CpuUtilization() {
  return _cpu;
}

// ________________________________________________________________________________________________
void Process::setUid(int uid) {
  _uid = uid;
}

// ________________________________________________________________________________________________
int Process::getUid() {
  return _uid;
}

// ________________________________________________________________________________________________
// Return the command that generated this process
string Process::Command() {
  return _command;
}

// ________________________________________________________________________________________________
// Return this process's memory utilization
string Process::Ram() {
  return _ram;
}
void Process::setCpuUtilization(float cpu) {
  _cpu = cpu;
}
// ________________________________________________________________________________________________
// Return the user (name) that generated this process
string Process::User() {
  return _userName;
}

// ________________________________________________________________________________________________
// Return the age of this process (in seconds)
int64_t Process::UpTime() {
  return _upTime; 
}

// ________________________________________________________________________________________________
// Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  // std::cout << _sortBy << std::endl;
  if (_sortBy == "cpu") { return _cpu > a._cpu; }
  if (_sortBy == "ram") { return _ram > a._ram; }
  if (_sortBy == "time") { return _upTime > a._upTime;}
  return _command < a._command;
}
