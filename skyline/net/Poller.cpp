
#include "skyline/net/Poller.h"
#include "skyline/net/Channel.h"

using namespace skyline;
using namespace skyline::net;

Poller::Poller(EventLoop* loop)
  : ownerLoop_(loop)
{
}

Poller::~Poller() = default;

bool Poller::hasChannel(Channel* channel) const
{
  asserInLoopThread();
  ChannelMap::const_iterator it = channels_.find(channel->fd());
  return it != channels_.end() && it->second == channel;
}
