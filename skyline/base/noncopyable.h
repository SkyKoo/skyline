#ifndef SKYLINE_BASE_NONCOPYABLE_H
#define SKYLINE_BASE_NONCOPYABLE_H

namespace skyline
{

class noncopyable
{
 public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

 protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

} // namespace skyline

#endif // SKYLINE_BASE_NONCOPYABLE_H
