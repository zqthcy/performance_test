#ifndef __JOB_HPP_
#define __JOB_HPP_

#include <process/future.hpp>

using namespace process;

class Job {
public:
  Job() {}
  virtual ~Job() {}

  virtual Future<int> run() = 0;

  //inline void run() {
    //this->doJob();
    //promise.future().onAny(
        //defer([=] (const Future<int>& future) {
          //terminate(self());
          //}));
    //return promise.future();
  /*}*/

  inline void done(int t) {
    promise.set(t);
  }

protected:
  Promise<int> promise;
};

#endif
