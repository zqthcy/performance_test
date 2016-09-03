#include <iostream>
#include "work_process.hpp"

using namespace std;

int main()
{
  cout << "Hello World!" << endl; 
  WorkProcess process;
  PID<WorkProcess> pid = spawn(&process);

  dispatch(pid, &WorkProcess::startWork, false);

  wait(pid);

  return 0;
}
