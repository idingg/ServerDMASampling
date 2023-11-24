#include <iostream>

#include "Output.h"
#include "Service.h"
#include "proc/ProcStat.h"
#include "proc/Type.h"

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