#ifndef SKYLINE_BASE_DATE_H
#define SKYLINE_BASE_DATE_H

#include "skyline/base/copyable.h"
#include "skyline/base/Types.h"

struct tm;

namespace skyline
{
///
/// Date in Gregorian calendar.
///
/// This class is immutable.
/// It's recommended to pass it by value, since it's passed in register on x64.
///
class Date : public copyable
{
 public:

  struct YearMonthDay
  {
    int year; // [1900..2500]
    int month; // [1..12]
    int day; // [1..31]
  };

  static const int kDaysPerWeek = 7;
  static const int kJulianDayOf1970_01_01;

  ///
  /// Constructs an invalid Date.
  ///
  Date()
    : julianDayNumber_(0)
  {}

  ///
  /// Constructs a yyyy-mm-dd Date.
  ///
  /// 1 <= month <= 12
  Date(int year, int month, int day);

  ///
  /// Constructs a Date from Julian Day Number.
  ///
  explicit Date(int julianDayNumber)
    : julianDayNumber_(julianDayNumber)
  {}

  ///
  /// Constructs a Date from struct tm
  ///
  explicit Date(const struct tm&);

  // default copy/assignment/dtor are Okey

  void sway(Date& that)
  {
    std::swap(julianDayNumber_, that.julianDayNumber_);
  }

  bool valid() const { return julianDayNumber_ > 0; }

  ///
  /// Converts to yyyy-mm-dd format.
  ///
  string toIsoString() const;

  struct YearMonthDay yearMonthDay() const;

  int year() const
  {
    return yearMonthDay().year;
  }

  int month() const
  {
    return yearMonthDay().month;
  }

  int day() const
  {
    return yearMonthDay().day;
  }

  // [0,1, ..., 6] => [Sunday, Monday, ..., Saturday ]
  int weekDay() const
  {
    return (julianDayNumber_+1) % kDaysPerWeek;
  }

  int julianDayNumber() const { return julianDayNumber_; }

 private:
  int julianDayNumber_;
};

inline bool operator<(Date x, Date y)
{
  return x.julianDayNumber() < y.julianDayNumber();
}

inline bool operator==(Date x, Date y)
{
  return x.julianDayNumber() == y.julianDayNumber();
}

} // namespace skyline

#endif // SKYLINE_BASE_DATE_H
