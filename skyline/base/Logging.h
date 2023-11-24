
#ifndef SKYLINE_BASE_LOGGING_H
#define SKYLINE_BASE_LOGGING_H

#include "skyline/base/LogStream.h"
#include "skyline/base/Timestamp.h"

namespace skyline
{

class Logger
{
 public:
  enum LogLevel
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL,
    NUM_LOG_LEVELS,
  };

  // compile time calculation of basename of source file
  class SourceFile
  {
  };

 private:

  // real implement class
  class Impl
  {
   public:
    typedef Logger::LogLevel LogLevel;
    Impl(LogLevel level, int old_errno, const SourceFile& file, int line);
    void formatTime();
    void finish();

    Timestamp time_;
    LogStream stream_;
    LogLevel level_;
    int line_;
    SourceFile basename_;
  };

  Impl impl_;
};

} // namespace skyline

#endif // SKYLINE_BASE_LOGGING_H
