
#ifndef SKYLINE_NET_SOCKETOPS_H
#define SKYLINE_NET_SOCKETOPS_H

#include <arpa/inet.h>

namespace skyline
{
namespace net
{
namespace sockets
{

ssize_t read(int sockfd, void *buf, size_t count);
ssize_t write(int sockfd, const void *buf, size_t count);
void close(int sockfd);

} // namespace socket
} // namespace net
} // namespace skyline

#endif // SKYLINE_NET_SOCKETOPS_H
