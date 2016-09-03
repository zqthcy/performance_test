#include <iostream>
#include <sstream>

#include <process/defer.hpp>
#include <process/dispatch.hpp>
#include <process/future.hpp>
#include <process/http.hpp>
#include <process/process.hpp>

using namespace process;

using namespace process::http;

using std::string;

class WorkProcess : public Process<WorkProcess>
{
public:
  WorkProcess() {}
  virtual ~WorkProcess() {}

  void startWork(bool stop)
  {
	  std::cout << "Done job." << std::endl;
    if (!stop) {
      sleep(5);
      dispatch(self(), &WorkProcess::startWork, stop);
    }
  }

  void stop(const UPID& from, const string& body)
  {
    terminate(self());
  }

protected:

private:
};
