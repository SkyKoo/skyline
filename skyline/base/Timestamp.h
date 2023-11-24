
#ifndef SKYLING_BASE_TIMESTAMP_H
#define SKYLING_BASE_TIMESTAMP_H

#include "skyline/base/copyable.h"
#include "skyline/base/Types.h"

namespace skyline
{

///
/// Time stamp in UTC, in microseconds resolution.
///
/// This class is immutable.
/// It's recommended to pass it by value, since it's passed in register on x64.
///
class Timestamp : public skyline::copyable
{
 public:
  ///
  /// Constructs an invalid Timestamp
  ///
  Timestamp()
    : microSecondsSinceEpoch_(0)
  {
  }

  ///
  /// Constructs a Timestamp at specific time
  ///
  /// @param microSecondsSinceEpoch_
  explicit Timestamp(int64_t microSecondsSinceEpochArg)
    : microSecondsSinceEpoch_(microSecondsSinceEpochArg)
  {
  }

  static Timestamp now();

  static const int kMicroSecondsPerSecond = 1000 * 1000;

 private:
  int64_t microSecondsSinceEpoch_;
};

} // namespace skyline

#endif // SKYLING_BASE_TIMESTAMP_H
