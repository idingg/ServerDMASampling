#pragma once
#ifndef _PROCSTAT
#define _PROCSTAT

#include <boost/algorithm/string/join.hpp>
#include <boost/filesystem.hpp>
#include <boost/thread.hpp>
#include <chrono>
#include <fstream>
#include <future>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "Service.hpp"
#include "Type.hpp"

class Proc {
 private:
  const std::string proc_path = "/proc";

 public:
  Proc(){};

 private:
  std::vector<Pid> getPids() {
    std::vector<Pid> ret;
    boost::filesystem::directory_iterator iter_end;
    for (boost::filesystem::directory_iterator iter(proc_path);
         iter != iter_end; ++iter) {
      bool is_dir = boost::filesystem::is_directory(iter->status());
      std::string filename = iter->path().filename().c_str();
      bool is_name_starts_number = filename[0] > '0';
      bool is_name_ends_number = filename[0] < '9';
      bool is_numeric_name = is_name_starts_number && is_name_ends_number;
      if (is_dir && is_numeric_name) {
        uint32_t pid = std::stoi(filename);
        ret.push_back(Pid(pid));
      }
    }
    return ret;
  }

  ProcStatData readProcStat(Pid pid) {
    std::string data = Service::ReadFile(
        proc_path + "/" + std::to_string(pid.ToUint32()) + "/stat");
    if (data != "") {
      return ProcStatData(data);
    }
    // std::cerr << "Unable to open file" << endl;
    return ProcStatData("");
  }

  uint64_t parseCpuClockValue(ProcStatData procStatData) {
    std::vector<std::string> tokens =
        Service::Split(procStatData.ToString(), ' ');
    uint64_t processUTime = std::stoi(tokens.at(13));
    uint64_t processSTime = std::stoi(tokens.at(14));
    uint64_t processTime = processUTime + processSTime;
    return processTime;
  }

 public:
  std::string getStatLog() {
    std::vector<std::string> procStats;
    std::vector<Pid> pids = getPids();
    for (Pid pid : pids) {
      std::string procStat = readProcStat(pid).ToString();
      procStats.push_back(procStat);
    }
    std::string ret = boost::algorithm::join(procStats, LineSeparator());
    return ret;
  }

  std::map<Pid, uint64_t> collectElapsedClocks() {
    std::map<Pid, uint64_t> elapsedClocks;
    std::vector<Pid> pids = getPids();
    for (Pid pid : pids) {
      ProcStatData procStat = readProcStat(pid);
      if (procStat.IsEmpty() == false) {
        elapsedClocks[pid] = parseCpuClockValue(procStat);
      }
    }
    return elapsedClocks;
  }

  double clocksToCpuPercent(const uint64_t clocks, const uint64_t ms) {
    double cpuUsage =
        (double)clocks / (double)ticksPerSecond * 100 / ((double)ms / msPerSec);
    return cpuUsage;
  }

  std::map<Pid, double> getCpuUsage(const uint64_t ms) {
    std::map<Pid, uint64_t> elapsedClocksAtStart = collectElapsedClocks();
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    std::map<Pid, uint64_t> elapsedClocksAtEnd = collectElapsedClocks();

    std::map<Pid, double> result;
    for (std::map<Pid, uint64_t>::iterator iter = elapsedClocksAtEnd.begin();
         iter != elapsedClocksAtEnd.end(); iter++) {
      Pid pid = iter->first;
      uint64_t clock = iter->second;
      std::map<Pid, uint64_t>::iterator found = elapsedClocksAtStart.find(pid);
      if (found != elapsedClocksAtStart.end()) {
        uint64_t clockDifference = clock - found->second;
        result[pid] = clocksToCpuPercent(clockDifference, ms);
      }
    }
    return result;
  }
};
#endif