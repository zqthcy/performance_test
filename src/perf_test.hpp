#include "test_job.hpp"
#include "work_process.hpp"

using namespace std;

class PerfTest {
public:
  PerfTest(int concurrency, int _count) : 
        concur(concurrency), count(_count) {
        workList = new WorkProcess*[concurrency]; 
        }
  ~PerfTest() {}

  int startTests();
private:
  int concur;
  int count;
  WorkProcess **workList;
};

inline int PerfTest::startTests()
{
  struct timeval tv;    
  gettimeofday(&tv,NULL);    
  WorkMeta *wm = new WorkMeta();
  wm->done = new atomic<int>(0); 
  wm->index = new atomic<int>(0); 
  wm->totalRT = new atomic<long>(0); 
  wm->st = tv.tv_sec * 1000000 + tv.tv_usec;
  for (int i = 0; i < concur; ++i) {
    int idx = std::atomic_fetch_add(
              wm->index, (int)1);
    workList[i] = new WorkProcess(wm, count, i);
    PID<WorkProcess> pid = spawn(workList[i]);
    Job* job = new TestJob(idx); 
    dispatch(pid, &WorkProcess::startWork, job);
  }
  wait(workList[0]);
  return 0;
}
