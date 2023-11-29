#ifndef SKYLINE_BASE_THREAD_H
#define SKYLINE_BASE_THREAD_H

#include "skyline/base/noncopyable.h"
#include "skyline/base/Types.h"
#include "skyline/base/CountDownLatch.h"
#include "skyline/base/Atomic.h"

#include <functional>
#include <pthread.h>

namespace skyline
{

class Thread : noncopyable
{
 public:
  typedef std::function<void ()> ThreadFunc;

  explicit Thread(ThreadFunc, const string& name = string());
  // FIXME: make it movable in C++11
  ~Thread();

  void start();
  int join(); // return pthread_join 

  bool started() const { return started_; }
  pid_t tid() const { return tid_; }
  const string& name() const { return name_; }

  static int numCreated() { return numCreated_.get(); }
 private:
  void setDefaultName();

  bool started_;
  bool joined_;
  pthread_t pthreadId_;
  pid_t tid_;
  ThreadFunc func_;
  string name_;
  // Why here's need CountDownLatch ?
  // could see https://www.zhihu.com/question/294270506/answer/489820748
  CountDownLatch latch_;

  static AtomicInt32 numCreated_;
};

} // namespace skyline

#endif // SKYLINE_BASE_THREAD_H
