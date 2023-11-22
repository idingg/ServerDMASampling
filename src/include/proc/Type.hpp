#pragma once
#ifndef _TYPE
#define _TYPE

#include <stdint.h>
#include <unistd.h>

#include <string>

struct Time {
  uint64_t sec;
  uint64_t nsec;
};

const uint64_t msPerSec = 1000;
const long ticksPerSecond = sysconf(_SC_CLK_TCK);

std::string LineSeparator() {
#ifdef _WIN32
  return "\r\n";  // Windows line separator
#else
  return "\n";  // Linux line separator
#endif
}

class ProcStatData {
 private:
  std::string data;

 public:
  ProcStatData() { data = ""; };

  ProcStatData(std::string data) { this->data = data; };

  const std::string ToString() { return data; }

  const bool IsEmpty() {
    if (data == "") {
      return true;
    }
    return false;
  }
};

class Pid {
 private:
  std::uint32_t pid;

 public:
  Pid() { pid = 0; };

  Pid(std::uint32_t pid) { this->pid = pid; };

  const uint32_t ToUint32() { return pid; }

  bool operator<(const Pid &pid) const { return this->pid < pid.pid; }

  const std::string ToString() { return std::to_string(pid); }

  const bool IsEmpty() {
    if (pid == 0) {
      return true;
    }
    return false;
  }
};
#endif