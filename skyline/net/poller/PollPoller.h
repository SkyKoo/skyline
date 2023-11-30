
#ifndef SKYLINE_NET_POLLER_POLLPOLLER_H
#define SKYLINE_NET_POLLER_POLLPOLLER_H

#include "skyline/net/Poller.h"

struct pollfd;

namespace skyline
{
namespace net
{

class PollPoller : public Poller
{
 public:
  PollPoller(EventLoop* loop);
  ~PollPoller() override;

  Timestamp poll(int timeoutMs, ChannelList* activeChannels) override;
  void updateChannel(Channel* channel) override;
  void removeChannel(Channel* channel) override;

 private:
  void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

  typedef std::vector<struct pollfd> PollFdList;
  PollFdList pollfds_;
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_POLLER_POLLPOLLER_H
