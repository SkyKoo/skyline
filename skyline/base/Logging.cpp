
#include "skyline/base/Logging.h"

#include "skyline/base/CurrentThread.h"

using namespace skyline;

Logger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile& file, int line)
  : time_(Timestamp::now()),
    stream_(),
    level_(level),
    line_(line),
    basename_(file)
{
  formatTime();
  CurrentThread::tid();
}

void Logger::Impl::formatTime()
{
}
