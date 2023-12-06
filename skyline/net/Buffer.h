
#ifndef SKYLINE_NET_BUFFER_H
#define SKYLINE_NET_BUFFER_H

#include "skyline/base/copyable.h"

namespace skyline
{
namespace net
{

/// A buffer class modeled after org.jboss.netty.buffer.ChannelBuffer
///
/// @code
/// +---------------------------------------------------------+
/// | prependable bytes |  readable bytes  |  writable bytes  |
/// |                   |     (CONTENT)    |                  |
/// +---------------------------------------------------------+
/// |                   |                  |                  |
/// 0      <=      readerIndex   <=   writerIndex    <=     size
/// @endcode
class Buffer : copyable
{
};

} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_BUFFER_H
