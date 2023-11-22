#include <iostream>

#include "Output.hpp"
#include "Service.hpp"
#include "proc/ProcStat.hpp"
#include "proc/Type.hpp"

using namespace std;

int main() {
#ifdef __linux__
  // Code to execute if the OS is Linux
  // cout << "linux" << endl;
#endif

  Proc ps;
  uint64_t interval_ms = 50;
  while (true) {
    Time start(Service::Now());
    map<Pid, double> cpu_usage = ps.getCpuUsage(interval_ms);
    Output::PrintCpuUsage(cpu_usage);
    Service::GetElapsedTimeFrom(start, interval_ms);
  }
  return 0;
}