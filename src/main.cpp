#include <iostream>
#include <atomic>
#include "test_job.hpp"
#include "work_process.hpp"

using namespace std;

int main()
{
  cout << "Hello World!" << endl; 
  WorkMeta *wm = new WorkMeta();
  wm->done = new atomic<int>(0); 

  WorkProcess process(wm, 10);
  PID<WorkProcess> pid = spawn(&process);

  Job* job = new TestJob(); 

  dispatch(pid, &WorkProcess::startWork, job);

  wait(pid);

  return 0;
}
