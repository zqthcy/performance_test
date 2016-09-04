#ifndef __JOB_HPP_
#define __JOB_HPP_

#include <process/future.hpp>

using namespace process;

class Job {
public:
  Job(int _id) : st(0), et(0), id(_id) {
    //std::cout << "id : " << id << std::endl;
  }
  /*Job() : st(0), et(0), id(0) {*/
    //std::cout << "id : " << id << std::endl;
  /*}*/
  virtual ~Job() {}

  virtual Future<int> work() = 0;

  virtual Future<int> run() {
    // st
    //std::cout << " Doing job, idx:" << idx << std::endl;
    return this->work();
  };

  inline void done(int idx) {
    // et
    //std::cout << " Job, idx:" << idx << " cost " << getCostTime() << " ms"<< std::endl;
    promise.set(idx);
  }

  long getCostTime() {
  //  std::cout << "Job " << id << " et:" << et << std::endl;;
   // std::cout << "Job " << id << " st:" << st << std::endl;;
    return (et - st);
  }

public:
  int id;

protected:
  Promise<int> promise;

private:
  long st;
  long et;
};

#endif
