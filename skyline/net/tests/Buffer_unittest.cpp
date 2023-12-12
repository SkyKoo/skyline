
#include "skyline/net/Buffer.h"

#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

using skyline::string;
using skyline::net::Buffer;

BOOST_AUTO_TEST_CASE(testBufferAppendRetrieve)
{
  Buffer buf;
  BOOST_CHECK_EQUAL(buf.readableBytes(), 0);
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize);
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend);

  // str : xxxxxxxxxx... 200
  const string str(200, 'x');
  buf.append(str);
  BOOST_CHECK_EQUAL(buf.readableBytes(), str.size()); // 200
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize - str.size()); // 1024 - 200
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend); // 8

  const string str2 = buf.retrieveAsString(50); // str2 : xxxxxxxxxx... 50
  BOOST_CHECK_EQUAL(str2.size(), 50); // 50
  BOOST_CHECK_EQUAL(buf.readableBytes(), str.size() - str2.size()); // 200 - 50
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize - str.size()); // 1024 - 50
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend + str2.size()); // 8 + 50
  BOOST_CHECK_EQUAL(str2, string(50, 'x')); // str2 : xxxxxxxxxx... 50

  buf.append(str);
  BOOST_CHECK_EQUAL(buf.readableBytes(), 2*str.size() - str2.size()); // 2*200 - 50
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize - 2*str.size()); // 1024 - 2*200
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend + str2.size()); // 1024 + 50

  const string str3 = buf.retrieveAllAsString();
  BOOST_CHECK_EQUAL(str3.size(), 350);
  BOOST_CHECK_EQUAL(buf.readableBytes(), 0);
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize);
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend);
  BOOST_CHECK_EQUAL(str3, string(350, 'x'));
}

BOOST_AUTO_TEST_CASE(testBufferGrow)
{
  Buffer buf;
  buf.append(string(400, 'y'));
  BOOST_CHECK_EQUAL(buf.readableBytes(), 400);
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize - 400);

  buf.retrieve(50);
  BOOST_CHECK_EQUAL(buf.readableBytes(), 350);
  BOOST_CHECK_EQUAL(buf.writableBytes(), Buffer::kInitialSize - 400);
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend + 50);

  buf.append(string(1000, 'z')); // buf.size() = 1000+400
  BOOST_CHECK_EQUAL(buf.readableBytes(), 1350);
  BOOST_CHECK_EQUAL(buf.writableBytes(), 0);
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend + 50); // FIXME

  buf.retrieveAll();
  BOOST_CHECK_EQUAL(buf.readableBytes(), 0);
  BOOST_CHECK_EQUAL(buf.writableBytes(), 1400); // FIXME
  BOOST_CHECK_EQUAL(buf.prependableBytes(), Buffer::kCheapPrepend);
}

BOOST_AUTO_TEST_CASE(testBufferInsideGrow)
{
  Buffer buf;
}

