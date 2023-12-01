#ifndef SKYLINE_NET_CALLBACKS_H
#define SKYLINE_NET_CALLBACKS_H

#include <functional>

namespace skyline
{

namespace net
{

typedef std::function<void()> TimerCallback;

} // namespace net

} // namespace skyline

#endif // SKYLINE_NET_CALLBACKS_H
