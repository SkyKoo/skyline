
#ifndef SKYLINE_BASE_COUNTDOWNLATCH_H
#define SKYLINE_BASE_COUNTDOWNLATCH_H

#include "skyline/base/Condition.h"
#include "skyline/base/Mutex.h"
#include "skyline/base/noncopyable.h"

namespace skyline
{

class CountDownLatch : noncopyable
{
 public:
  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  Condition condition_ GUARDED_BY(mutex_);
  int count_ GUARDED_BY(mutex_);
};

} // namespace skyline

#endif // SKYLINE_BASE_COUNTDOWNLATCH_H
