
#ifndef SKYLINE_BASE_TYPES_H
#define SKYLINE_BASE_TYPES_H

#include <stdint.h>
#include <string.h> // memset
#include <string>

///
/// The most common stuffs.
///
namespace skyline
{

using std::string;

inline void memZero(void* p, size_t n)
{
  memset(p, 0, n);
}

//
// Use implicit_cast as a safe version of static_cast or const_cast
// for upcasting in the type hierarchy (i.e. casting a pointer to Foo
// to a pointer to SuperclassOfFoo or casting a pointer to Foo to
// a const pointer to Foo).
// When you use implicit_cast, the compiler checks that the cast is safe.
// Such explicit implicit_cast are necessary in superisingly many
// situations where C++ demands an exact type match instead of an
// argument type convertable to a target type.
//
// The From type can be inferred, so the preferred syntax for using
// implicit_cast is the same as for static_cast etc.:
//
//   implicit_cast<ToType>(expr)
//
// implicit_cast would have been part of the C++ standard library,
// but the proposal was submitted too late. It will probably make
// its way into the language in the future.
template<typename To, typename From>
inline To implicit_cast(From const &f)
{
  return f;
}

}

#endif // SKYLINE_BASE_TYPES_H
