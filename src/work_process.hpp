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
  WorkProcess(WorkMeta* _workMeta, int _totalCnt, int _id) 
    : workMeta(_workMeta), totalCnt(_totalCnt), id(_id) {}
  virtual ~WorkProcess() {}

  void startWork(Job* job)
  {
    Future<int> jobFuture;
    if (job->id < totalCnt) {
      jobFuture = job->run();
      std::cout << "Job " << job->id <<  " cost :" << job->getCostTime() << std::endl;
      int idx = std::atomic_fetch_add(
              workMeta->index, (int)1);
      dispatch(self(), &WorkProcess::startWork, new TestJob(idx));
    } else {
      return;
    }

    // TODO in Server
    job->done(job->id);

    jobFuture.onAny(
        defer(self(), [=] (const Future<int>& future) {
      //    sleep(1);
          int t = future.get(); 
          std::cout << id << " DoneJob, index:" << job->id << std::endl;
          // rt = getCostTime
          std::atomic_fetch_add(
              workMeta->totalRT, job->getCostTime());

          int cnt = std::atomic_fetch_add(
              workMeta->done, (int)1);
          
          if (cnt == totalCnt - 1) {
            struct timeval tv;    
            gettimeofday(&tv,NULL);    
            workMeta->et = tv.tv_sec * 1000 + tv.tv_usec / 1000;
            long cost = workMeta->et - workMeta->st;
            std::cout << "Total cost time:" << cost << " ms" << std::endl;
            std::cout << "QPS:" << ((float)totalCnt / cost) * 1000000 << " 次/s" << std::endl;

            long totalRt = workMeta->totalRT->load(std::memory_order_seq_cst);
            std::cout << "Total RT :" << totalRt << std::endl;
          }

          if (cnt >= totalCnt - 1) {
            terminate(self());
          }
          }));
  }

  void stop(const UPID& from, const string& body)
  {
    terminate(self());
  }

protected:

private:
  WorkMeta* workMeta;
  int totalCnt;
  int id;
};

#endif
