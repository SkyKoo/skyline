#include "skyline/base/Logging.h"
// #include "skyline/base/LogFile.h"

#include <unistd.h>

int g_total;
FILE* g_file;
// std::unique_ptr<skyline::LogFile> g_logFile;

void dummyOutput(const char* msg, int len)
{
}

void bench(const char* type)
{
  // skyline::Logger::setOutput(dummyOutput);
}

int main()
{
  LOG_TRACE << "trace";
  LOG_DEBUG << "debug";
  LOG_INFO << "Hello";
  LOG_WARN << "World";
  LOG_ERROR << "Error";

  sleep(1); // must sleep 1 second, the timezone can take effect

  skyline::TimeZone beijing(8*3600, "CST");
  skyline::Logger::setTimeZone(beijing);
  LOG_TRACE << "trace CST";
  LOG_DEBUG << "debug CST";
  LOG_INFO << "Hello CST";
  LOG_WARN << "World CST";
  LOG_ERROR << "Error CST";

  return 0;
}
