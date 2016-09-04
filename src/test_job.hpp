#ifndef __TESTJOB_HPP_
#define __TESTJOB_HPP_

#include "job.hpp"
#include <process/future.hpp>

using namespace process;

class TestJob : public Job {
public:
  TestJob() {}
  virtual ~TestJob() {}

  virtual Future<int> run();
private:
};

Future<int> TestJob::run()
{
  return promise.future();
}

#endif
