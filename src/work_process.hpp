#ifndef __WORK_PROCESS_HPP_
#define __WORK_PROCESS_HPP_

#include <iostream>
#include <sstream>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>
#include "job.hpp"
#include "work_meta.hpp"

using namespace process;

using namespace process::http;

using std::string;

class WorkProcess : public Process<WorkProcess>
{
public:
  WorkProcess(WorkMeta* _workMeta, int _totalCnt) 
    : workMeta(_workMeta), totalCnt(_totalCnt) {}
  virtual ~WorkProcess() {}

  void startWork(Job* job)
  {
    int cnt = std::atomic_fetch_add(
        workMeta->done, (int)1);
    if (cnt < totalCnt) {
      job->done(cnt);
      job->run().onAny(
          defer(self(), [] (const Future<int>& future) {
            int t = future.get(); 
            std::cout << "DoneJob, index:" << t << std::endl;
            }));
      std::cout << "Start Job Ok, index:" << cnt << std::endl;
      sleep(1);
      dispatch(self(), &WorkProcess::startWork, new TestJob());
    }
  }

  void stop(const UPID& from, const string& body)
  {
    terminate(self());
  }

protected:

private:
  WorkMeta* workMeta;
  int totalCnt;
};

#endif
