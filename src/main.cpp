#include <iostream>
#include <atomic>
#include "perf_test.hpp"

using namespace std;

int main()
{
  cout << "Hello World!" << endl; 

  // PerfTest 
  // 1.concurrency, 2.test count
  PerfTest perfTest(3, 6);
  perfTest.startTests();

  return 0;
}
