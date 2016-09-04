#ifndef __WORK_META_HPP_
#define __WORK_META_HPP_

#include <atomic>

struct WorkMeta {
  std::atomic<int>* done;
  long st;
  long et;
  std::atomic<int>* index;
  std::atomic<long>* totalRT;
};


#endif
