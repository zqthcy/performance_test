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

class MyProcess : public Process<MyProcess>
{
public:
  MyProcess() {}
  virtual ~MyProcess() {}

  void testFunc(int i)
  {
	  std::cout << "Test " << i << std::endl;
  }

  void stop(const UPID& from, const string& body)
  {
    terminate(self());
  }

protected:

private:
};
