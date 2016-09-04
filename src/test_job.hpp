#ifndef __TESTJOB_HPP_
#define __TESTJOB_HPP_

#include "job.hpp"
#include <process/future.hpp>

using namespace process;

class TestJob : public Job {
public:
  TestJob(int id) : Job(id) {}

  virtual ~TestJob() {}

  virtual Future<int> work();
private:
};

Future<int> TestJob::work()
{
  return promise.future();
}

#endif
