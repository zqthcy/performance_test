#ifndef __WORK_META_HPP_
#define __WORK_META_HPP_

#include <atomic>

struct WorkMeta {
  std::atomic<int>* done;
};


#endif
