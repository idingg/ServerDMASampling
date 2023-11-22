#pragma once
#ifndef _OUTPUT
#define _OUTPUT

#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>

#include "Service.hpp"
#include "Type.hpp"

class Output {
 private:
  static const int cpu_usage_precision = 1;

 public:
  Output(){};

  static std::string PrintCpuUsage(std::map<Pid, double> map) {
    std::string ret = "";
    for (auto iter = map.begin(); iter != map.end(); iter++) {
      Pid pid = iter->first;
      double cpu_usage = iter->second;
      if (pid.IsEmpty() == false) {
        std::string fixed =
            Service::DoubleToFixedString(cpu_usage, cpu_usage_precision);
        ret += pid.ToString() + " " + fixed + LineSeparator();
      }
    }
    std::cout << ret;
    return ret;
  }
};
#endif
