
#ifndef SKYLINE_BASE_LOGGING_H
#define SKYLINE_BASE_LOGGING_H

#include "skyline/base/LogStream.h"
#include "skyline/base/Timestamp.h"
#include "skyline/base/TimeZone.h"

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
   public:
    template<int N>
    SourceFile(const char (&arr)[N])
      : data_(arr),
        size_(N-1)
    {
      const char* slash = strrchr(data_, '/'); // builtin function
      if (slash)
      {
        data_ = slash + 1;
        size_ -= static_cast<int>(data_ - arr); // actually size_ -= 1
      }
    }

    explicit SourceFile(const char* filename)
      : data_(filename)
    {
      const char* slash = strrchr(filename, '/');
      if (slash)
      {
        data_ = slash + 1;
      }
      size_ = static_cast<int>(strlen(data_));
    }

    const char* data_;
    int size_;
  };

  Logger(SourceFile file, int line);
  Logger(SourceFile file, int line, LogLevel level);
  Logger(SourceFile file, int line, LogLevel level, const char* func);
  Logger(SourceFile file, int line, bool toAbort);
  ~Logger();

  LogStream& stream() { return impl_.stream_; }

  static LogLevel logLevel();
  static void setLogLevel(LogLevel level);

  typedef void (*OutputFunc)(const char* msg, int len);
  typedef void (*FlushFunc)();
  static void setOutput(OutputFunc);
  static void setFlush(FlushFunc);
  static void setTimeZone(const TimeZone& tz);

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

extern Logger::LogLevel g_logLevel;

inline Logger::LogLevel Logger::logLevel()
{
  return g_logLevel;
}

//
// CAUTION: do not write:
//
// if (good)
//  LOG_INFO << "Good news";
// else
//  LOG_WARN << "Bad news";
//
// this expends to, means this need to add "{}"?
//
// if (good)
//   if (logging_INFO)
//     logInfoStream << "Good news";
//   else
//     logWarnStream << "Bad news";
//
#define LOG_TRACE if (skyline::Logger::logLevel() <= skyline::Logger::TRACE) \
  skyline::Logger(__FILE__, __LINE__, skyline::Logger::TRACE, __func__).stream()
#define LOG_DEBUG if (skyline::Logger::logLevel() <= skyline::Logger::DEBUG) \
  skyline::Logger(__FILE__, __LINE__, skyline::Logger::DEBUG, __func__).stream()
#define LOG_INFO if (skyline::Logger::logLevel() <= skyline::Logger::INFO) \
  skyline::Logger(__FILE__, __LINE__).stream()
#define LOG_WARN skyline::Logger(__FILE__, __LINE__, skyline::Logger::WARN, __func__).stream()
#define LOG_ERROR skyline::Logger(__FILE__, __LINE__, skyline::Logger::ERROR, __func__).stream()
#define LOG_FATAL skyline::Logger(__FILE__, __LINE__, skyline::Logger::FATAL, __func__).stream()
#define LOG_SYSERR skyline::Logger(__FILE__, __LINE__, false).stream()
#define LOG_SYSFATAL skyline::Logger(__FILE__, __LINE__, true).stream()

const char* strerror_tl(int savedErrno);

// Taken from glog/logging.h
//
// Check that the input is non NULL. This very useful in constructor
// initializer lists.

#define CHECK_NOTNULL(val) \
  ::skyline::CheckNotNull(__FILE__, __LINE__, "'" #val "' Must be non NULL", (val))

// A small helper for Check_NOTNULL().
template <typename T>
T* CheckNotNull(Logger::SourceFile file, int line, const char *names, T* ptr)
{
  if (ptr == NULL)
  {
    Logger(file, line, Logger::FATAL).stream() << names;
  }
  return ptr;
}

} // namespace skyline

#endif // SKYLINE_BASE_LOGGING_H
