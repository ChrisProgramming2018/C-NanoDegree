// Copyright 2020
// Udacity Project
// Author: Christian Leininger <info2016frei@gmail.com>


#ifndef CPPND_SYSTEM_MONITOR_INCLUDE_LINUX_PARSER_H_
#define CPPND_SYSTEM_MONITOR_INCLUDE_LINUX_PARSER_H_

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {
  // Paths

  //const std::string kProcDirectory{"/proc/"};
  constexpr char const* kProcDirectory = "/proc/";
  constexpr char const* kCmdlineFilename = "/cmdline";
  constexpr char const* kCpuinfoFilename = "/cpuinfo";
  constexpr char const* kStatusFilename = "/status";
  constexpr char const* kStatFilename = "/stat";
  constexpr char const* kUptimeFilename = "/uptime";
  constexpr char const* kMeminfoFilename = "/meminfo";
  constexpr char const* kVersionFilename = "/version";
  constexpr char const* kOSPath = "/etc/os-release";
  constexpr char const* kPasswordPath = "/etc/passwd";
  // System
  float MemoryUtilization();
  long UpTime();
  std::vector<int> Pids();
  int TotalProcesses();
  int RunningProcesses();
  std::string OperatingSystem();
  std::string Kernel();
  float ProcessCpuUtilization(int pid);

  const std::string kNumbers = "0123456789";
  const std::string kLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  // CPU
  enum CPUStates {
    kUser_ = 0,
    kNice_,
    kSystem_,
    kIdle_,
    kIOwait_,
    kIRQ_,
    kSoftIRQ_,
    kSteal_,
    kGuest_,
    kGuestNice_
  };
  std::vector<std::string> CpuUtilization();
  long Jiffies();
  long ActiveJiffies();
  long ActiveJiffies(int pid);
  long IdleJiffies();

  // Processes
  std::string Command(int pid);
  std::string Ram(int pid);
  int Uid(int pid);
  std::string User(int pid);
  long UpTime(int pid);


  // Memory
  float getMemoryUtilization();

  // Uptime
  long getUpTime();
};  // namespace LinuxParser

#endif  // CPPND_SYSTEM_MONITOR_INCLUDE_LINUX_PARSER_H_
