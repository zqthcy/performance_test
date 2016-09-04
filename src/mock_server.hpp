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

class MockServerProcess : public Process<MockServerProcess>
{
public:
  MockServerProcess() {}
  virtual ~MockServerProcess() {}

protected:

private:
};
