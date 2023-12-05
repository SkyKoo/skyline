#include "skyline/base/Thread.h"
#include "skyline/net/EventLoop.h"

#include <unistd.h> // getpid()
#include <assert.h>

using namespace skyline;
using namespace skyline::net;

EventLoop* g_loop;

void callback()
{
  printf("callback(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
  // EventLoop anotherLoop; // one thread only can exist one eventloop
}

void threadFunc()
{
  printf("threadFunc(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());

  assert(EventLoop::getEventLoopOfCurrentThread() == NULL);
  EventLoop loop;
  assert(EventLoop::getEventLoopOfCurrentThread() == &loop);
  loop.runAfter(1.0, callback);
  // loop.runEvery(1.0, callback);
  loop.loop();
}

int main()
{
  printf("main(): pid = %d, tid = %d\n", getpid(), CurrentThread::tid());

  assert(EventLoop::getEventLoopOfCurrentThread() == NULL);
  EventLoop loop;
  assert(EventLoop::getEventLoopOfCurrentThread() == &loop);

  Thread thread(threadFunc);
  thread.start();

  loop.loop();
}
