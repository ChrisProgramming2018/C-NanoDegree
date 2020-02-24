// Copyright 2020
// // Udacity Project
// // Author: Christian Leininger <info2016frei@gmail.com>


#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>

#include "../include/linux_parser.h"
#include "../include/format.h"
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
  std::string totalMemory = "MemTotal:";
  std::string usedMemory = "MemAvailable:";
  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  int start;
  int end;
  int valueTotalMemory;
  float valueMemAvailable;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      size_t found = line.find(totalMemory);
      if (found != std::string::npos) {
        start = line.find_first_of(kNumbers);
        end = line.find_last_of(kNumbers);
        valueTotalMemory =  std::stoi(line.substr(start, end));
      }
      found = line.find(usedMemory);
      if (found != std::string::npos) {
        start = line.find_first_of(kNumbers);
        end = line.find_last_of(kNumbers);
        valueMemAvailable =  std::stoi(line.substr(start, end));
      }
    }
  }
  float percentUsed = (valueTotalMemory - valueMemAvailable) / valueTotalMemory;
  return percentUsed;
}

// Read and return the system uptime
// _____________________________________________________________________
int64_t LinuxParser::UpTime() {
  std::string line;
  int64_t upTime;
  int start;
  int end;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      start = line.find_first_of(kNumbers);
      end  = line.find_first_not_of(kNumbers);
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



// Read and return the number of jiffies for the system
// _____________________________________________________________________
int64_t LinuxParser::Jiffies() {
  return 0;
}

// Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
int64_t LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) {
  return 0;
}


//  Read and return the number of active jiffies for the system
// _____________________________________________________________________
int64_t LinuxParser::ActiveJiffies() {
  return 0;
}

//  Read and return the number of idle jiffies for the system
// _____________________________________________________________________
int64_t LinuxParser::IdleJiffies() {
  return 0;
}

// Read and return CPU utilization
// _____________________________________________________________________
vector<string> LinuxParser::CpuUtilization() {
  string line;
  string key = "cpu";
  size_t found;
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
  std::string line;
  std::string de;
  int start;
  int totalProcesses;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  while (std::getline(filestream, line)) {
    std::size_t found = line.find("processes");
    if (found != std::string::npos) {
      start = line.find_first_of(kNumbers);
      totalProcesses = std::stoi(line.substr(start));
    }
  }
  return totalProcesses;
}

// Read and return the number of running processes
// _____________________________________________________________________
int LinuxParser::RunningProcesses() {
  return static_cast<int>(Pids().size());;
}

// Read and return the command associated with a process
// _____________________________________________________________________
string LinuxParser::Command(int pid) {
  std::string line;
  std::string rest;
  int start;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  while (std::getline(filestream, line)) {
    std::size_t found = line.find("Name:");
    if (found != std::string::npos) {
      start = line.find_first_not_of(kLetters);
      rest  = line.substr(start);
      start = rest.find_first_of(kLetters);
      rest  = rest.substr(start);
    return rest;
    }
  }
  return string();
}

// Read and return the memory used by a process
// _____________________________________________________________________
string LinuxParser::Ram(int pid) {
  std::string line;
  std::string rest;
  int start;
  int end;
  int res;
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  while (std::getline(filestream, line)) {
    std::size_t found = line.find("VmData:");
    if (found != std::string::npos) {
      // std::cout << "Pid " << pid  << std::endl;
      start = line.find_first_of(kNumbers);
      rest  =  line.substr(start);
      end = rest.find_first_not_of(kNumbers);
      rest = line.substr(start, end);
      res = std::stoi(rest);
    }
  }
  res = res / 1024;
  return std::to_string(res);
}

//  Read and return the user ID associated with a process
// _____________________________________________________________________
int LinuxParser::Uid(int pid) {
  int uid, start, end;
  std::string line, rest;
  std::string key = "Uid:";
  std::string path = "/proc/" + std::to_string(pid) + "/status";
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::size_t found = line.find(key);
      if (found != std::string::npos) {
        start = line.find_first_of(kNumbers);
        rest  =  line.substr(start);
        end = rest.find_first_not_of(kNumbers);
        rest = line.substr(start, end);
        uid = std::stoi(rest);
      }
    }
  }
  return uid;
}

// Read and return the user associated with a process
// _____________________________________________________________________
string LinuxParser::User(int pid) {
  int end;
  std::string line, rest;
  std::string path = "/etc/passwd";
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::size_t found = line.find(std::to_string(pid));
      if (found != std::string::npos) {
        end = line.find_first_not_of(kLetters);
        rest  =  line.substr(0, end);
        // std::cout << rest << std::endl;
      }
    }
  }
  return rest;
}
// _____________________________________________________________________
float LinuxParser::ProcessCpuUtilization(int pid) {
  std::string line;
  std::string path = "/proc/" + std::to_string(pid) + "/stat";
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  std::istringstream iss(line);
  int64_t utime;
  int64_t stime;
  int64_t cutime;
  int64_t cstime;
  int64_t startTime;
  int count = 1;
  do {
    std::string subs;
    iss >> subs;
    if (count == 14) utime = std::stoi(subs);
    if (count == 15) stime = std::stoi(subs);
    if (count == 16) cutime = std::stoi(subs);
    if (count == 17) cstime = std::stoi(subs);
    if (count == 22) startTime = std::stoi(subs);
    count++;
  } while (iss);

  int totalTime = utime + stime;
  totalTime = totalTime + cutime + cstime;
  int Hertz = 100;
  float seconds = UpTime() - (startTime/ Hertz);
  return (totalTime / Hertz) / seconds;
}


// Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
// _____________________________________________________________________
int64_t  LinuxParser::UpTime(int pid) {
  std::string line;
  std::string path = "/proc/" + std::to_string(pid) + "/stat";
  std::ifstream filestream(path);
  if (filestream.is_open()) {
    std::getline(filestream, line);
  }
  std::istringstream iss(line);

  int64_t utime;
  int64_t stime;
  int64_t cutime;
  int64_t cstime;
  int64_t startTime;
  int count = 1;
  do {
    std::string subs;
    iss >> subs;
    if (count == 14) utime = std::stoi(subs);
    if (count == 15) stime = std::stoi(subs);
    if (count == 16) cutime = std::stoi(subs);
    if (count == 17) cstime = std::stoi(subs);
    if (count == 22) startTime = std::stoi(subs);
    count++;
  } while (iss);

  int totalTime = utime + stime;
  totalTime = totalTime + cutime + cstime;

  return   UpTime() - (startTime/100);
}
