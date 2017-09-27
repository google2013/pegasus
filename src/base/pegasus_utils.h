// Copyright (c) 2017, Xiaomi, Inc.  All rights reserved.
// This source code is licensed under the Apache License Version 2.0, which
// can be found in the LICENSE file in the root directory of this source tree.

#pragma once

#include <time.h>
#include <cctype>
#include <boost/lexical_cast.hpp>
#include <dsn/cpp/address.h>

namespace pegasus {
namespace utils {

// it's seconds since 2016.01.01-00:00:00 GMT
const uint32_t epoch_begin = 1451606400;
inline uint32_t epoch_now() { return time(nullptr) - epoch_begin; }

// extract "host" from rpc_address
void addr2host(const ::dsn::rpc_address &addr, char *str, int len);

// parse int from string
bool buf2int(const char *buffer, int length, int &result);
bool buf2int64(const char *buffer, int length, int64_t &result);

// ----------------------------------------------------------------------
// c_escape_string()
//    Copies 'src' to 'dest', escaping dangerous characters using
//    '0xFF'-style escape sequences.  'src' and 'dest' should not overlap.
//    Returns the number of bytes written to 'dest' (not including the \0)
//    or (size_t)-1 if there was insufficient space.
// ----------------------------------------------------------------------
size_t c_escape_string(const char *src, size_t src_len, char *dest, size_t dest_len);

// T must support data() and length() method.
template <class T>
std::string c_escape_string(const T &src)
{
    const size_t dest_len = src.length() * 4 + 1; // Maximum possible expansion
    char *dest = new char[dest_len];
    const size_t used = c_escape_string(src.data(), src.length(), dest, dest_len);
    std::string s(dest, used);
    delete[] dest;
    return s;
}

// ----------------------------------------------------------------------
// c_unescape_string()
//    Copies 'src' to 'dest', unescaping '0xFF'-style escape sequences to
//    original characters.
//    Returns the number of bytes written to 'dest' (not including the \0)
//    or (-n) if unescape failed, where n is the failure position.
// ----------------------------------------------------------------------
int c_unescape_string(const std::string &src, std::string &dest);
}
} // namespace
