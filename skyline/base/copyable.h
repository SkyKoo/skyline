#ifndef SKYLINE_BASE_COPYABLE_H
#define SKYLINE_BASE_COPYABLE_H

namespace skyline
{

/// A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable shoud be a value type.
class copyable
{
 protected:
  copyable() = default;
  ~copyable() = default;
};

} // namespace skyline

#endif // SKYLINE_BASE_COPYABLE_H
