#pragma once
#ifndef _SERVICE
#define _SERVICE

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "proc/Type.h"

class Service {
 private:
 public:
  static const std::string ReadFile(const std::string path) {
    std::ifstream file(path);
    if (file.is_open()) {
      std::string summary;
      std::string line;
      while (getline(file, line)) {
        summary += line;
      }
      file.close();
      return summary;
    }
    // cerr << "Unable to open file" << endl;
    return "";
  }
  static const std::string DoubleToFixedString(const double value,
                                               const int precision) {
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(precision) << value;
    return stream.str();
  }

  static std::vector<std::string> Split(const std::string str,
                                        const char delimiter) {
    std::istringstream stream(str);
    std::vector<std::string> result;
    std::string token;
    while (getline(stream, token, delimiter)) {
      result.push_back(token);
    }
    return result;
  }
  static const Time Now() {
    std::chrono::_V2::system_clock::time_point now =
        std::chrono::high_resolution_clock::now();
    Time time;

    time.sec =
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch())
            .count();
    time.nsec = std::chrono::duration_cast<std::chrono::nanoseconds>(
                    now.time_since_epoch())
                    .count() %
                static_cast<int64_t>(1e9);
    return time;
  }

  static void GetElapsedTimeFrom(const Time time,
                                 const uint64_t sleep_time_ms) {
    Time now = Now();
    double sec = now.sec - time.sec;
    double nsec = ((double)now.nsec - time.nsec) * 1e-9;
    double sleep_time = sleep_time_ms * 1e-3;

    std::string formated = DoubleToFixedString(sec + nsec - sleep_time, 9);
    std::cout << "Elapsed time: " << formated << " sec" << std::endl;
  }
};
#endif