
#include "skyline/net/SocketsOps.h"

#include "skyline/base/Logging.h"

#include <unistd.h>

using namespace skyline;
using namespace skyline::net;

namespace
{

typedef struct sockaddr SA;

} // namespace

ssize_t sockets::read(int sockfd, void *buf, size_t count)
{
  return ::read(sockfd, buf, count);
}

ssize_t sockets::write(int sockfd, const void *buf, size_t count)
{
  return ::write(sockfd, buf, count);
}

void sockets::close(int sockfd)
{
  if (::close(sockfd) < 0)
  {
    LOG_SYSERR << "sockets::close";
  }
}
