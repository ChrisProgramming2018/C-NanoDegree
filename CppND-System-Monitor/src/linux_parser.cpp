#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
// _____________________________________________________________________
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
// _____________________________________________________________________
string LinuxParser::Kernel() {
  string os, version,  kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;

  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
// _____________________________________________________________________
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}


// _____________________________________________________________________
float LinuxParser::getMemoryUtilization() {
  std::string line;
  std::string allInt = "0123456789";
  std::string totalMemory = "MemTotal:";
  std::string usedMemory = "MemAvailable:" ;
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  int start;
  int end;
  int valueTotalMemory;
  float valueMemAvailable;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      int found = line.find(totalMemory);
      if (found!=std::string::npos) {
        start = line.find_first_of(allInt);
        end = line.find_last_of(allInt);
        valueTotalMemory =  std::stoi(line.substr(start, end));
      }
      found = line.find(usedMemory);
      if (found!=std::string::npos) {
        start = line.find_first_of(allInt);
        end = line.find_last_of(allInt);
        valueMemAvailable =  std::stoi(line.substr(start, end));
      }
    }
  }
  float percentUsed = (valueTotalMemory - valueMemAvailable) / valueTotalMemory;
  // std::cout << "number av " << percentUsed << std::endl;
  return percentUsed;
}

// Read and return the system uptime
// _____________________________________________________________________
long LinuxParser::UpTime() {
  std::string allInt = "0123456789";
  std::string line;
  long int upTime;
  int start;
  int end;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      start = line.find_first_of(allInt);
      end  = line.find_first_not_of(allInt);
      upTime = std::stoi(line.substr(start, end));
    }
  }
  return upTime;
}

// Read and return the system memory utilization
// _____________________________________________________________________
float LinuxParser::MemoryUtilization() { 
  return getMemoryUtilization(); 
}

   

// TODO: Read and return the number of jiffies for the system
// _____________________________________________________________________
long LinuxParser::Jiffies() { 
  return 0; 
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { 
  return 0; 
}


// TODO: Read and return the number of active jiffies for the system
// _____________________________________________________________________
long LinuxParser::ActiveJiffies() { 
  return 0; 
}

// TODO: Read and return the number of idle jiffies for the system
// _____________________________________________________________________
long LinuxParser::IdleJiffies() { 
  return 0; 
}

// Read and return CPU utilization
// _____________________________________________________________________
vector<string> LinuxParser::CpuUtilization() { 
  string line;
  string key = "cpu";
  std::cout << "linuxparser " << std::endl;
  int found;
  vector<string> cpus = {};
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      found = line.find(key);
      if (found != std::string::npos) {
        cpus.push_back(line);
      }
    }
  }
      

  return cpus; 
}

// Read and return the total number of processes
// _____________________________________________________________________
int LinuxParser::TotalProcesses() { 
  std::string allInt = "0123456789";
  std::string line;
  std::string de;
  int start;
  int totalProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
    while (std::getline(filestream, line)) {
      std::size_t found = line.find("processes");
      if (found!=std::string::npos) {
        start = line.find_first_of(allInt);
        totalProcesses = std::stoi(line.substr(start));
      }
      // start = line.find_first_of(allInt);
      //end  = line.find_first_not_of(allInt);
      // upTime = std::stoi(line.substr(start, end));
      // // std::cout << "number av " << percentUsed << std::endl;
      // // std::cout << "number av " << percentUsed << std::endl;
    }
    return totalProcesses;
}

// TODO: Read and return the number of running processes
// _____________________________________________________________________
int LinuxParser::RunningProcesses() { 
  return 0; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
string LinuxParser::Command(int pid[[maybe_unused]]) { 
  return string(); 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
string LinuxParser::Ram(int pid[[maybe_unused]]) { 
  return string(); 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
string LinuxParser::Uid(int pid[[maybe_unused]]) { 
  return string(); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
string LinuxParser::User(int pid[[maybe_unused]]) { 
  return string(); 
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
long int LinuxParser::UpTime(int pid[[maybe_unused]]) { 
  return 0; 
}
