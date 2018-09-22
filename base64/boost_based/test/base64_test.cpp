//
// base64_test.cpp
//
// Created on: Sep 21, 2018
//     Author: alexen
//

#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <iostream>
#include <base64/boost_based/base64.h>


namespace {
namespace aux {


struct inmem_streambuf : std::streambuf {
     inmem_streambuf( const char* data, std::size_t len ) {
          setg(
               const_cast<char*>( data ),
               const_cast<char*>( data ),
               const_cast<char*>( data + len )
               );
     }
     inmem_streambuf( const std::string& str )
          : inmem_streambuf( str.data(), str.size() ) {}
};


struct binary_streambuf : std::streambuf {
     binary_streambuf( const unsigned char* data, std::size_t len ) {
          setg(
               reinterpret_cast<char*>( const_cast<unsigned char*>( data ) ),
               reinterpret_cast<char*>( const_cast<unsigned char*>( data ) ),
               reinterpret_cast<char*>( const_cast<unsigned char*>( data + len ) )
               );
     }
};


} // namespace aux
} // namespace {unnamed}


TEST( BoostBased, EncodeEmptyString )
{
     aux::inmem_streambuf sbuf{ "", 0 };
     std::istream is{ &sbuf };
     std::ostringstream os;

     ASSERT_NO_THROW( base64::boost_based::encode( is, os ) );
     ASSERT_TRUE( os.str().empty() );
}


TEST( BoostBased, EncodeTextString )
{
     const std::string text =
          "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
          "sed do eiusmod tempor incididunt ut labore et dolore magna "
          "aliqua. Ut enim ad minim veniam, quis nostrud exercitation "
          "ullamco laboris nisi ut aliquip ex ea commodo consequat. "
          "Duis aute irure dolor in reprehenderit in voluptate velit "
          "esse cillum dolore eu fugiat nulla pariatur. Excepteur "
          "sint occaecat cupidatat non proident, sunt in culpa qui "
          "officia deserunt mollit anim id est laborum.";
     const std::string expected =
          "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaX"
          "Bpc2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIGluY2lkaWR1"
          "bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYSBhbGlxdWEuIFV0IGVuaW"
          "0gYWQgbWluaW0gdmVuaWFtLCBxdWlzIG5vc3RydWQgZXhlcmNpdGF0aW9u"
          "IHVsbGFtY28gbGFib3JpcyBuaXNpIHV0IGFsaXF1aXAgZXggZWEgY29tbW"
          "9kbyBjb25zZXF1YXQuIER1aXMgYXV0ZSBpcnVyZSBkb2xvciBpbiByZXBy"
          "ZWhlbmRlcml0IGluIHZvbHVwdGF0ZSB2ZWxpdCBlc3NlIGNpbGx1bSBkb2"
          "xvcmUgZXUgZnVnaWF0IG51bGxhIHBhcmlhdHVyLiBFeGNlcHRldXIgc2lu"
          "dCBvY2NhZWNhdCBjdXBpZGF0YXQgbm9uIHByb2lkZW50LCBzdW50IGluIG"
          "N1bHBhIHF1aSBvZmZpY2lhIGRlc2VydW50IG1vbGxpdCBhbmltIGlkIGVz"
          "dCBsYWJvcnVtLg==";

     aux::inmem_streambuf sbuf{ text };
     std::istream is{ &sbuf };
     std::ostringstream os;

     ASSERT_NO_THROW( base64::boost_based::encode( is, os ) );
     ASSERT_FALSE( os.str().empty() );
     ASSERT_EQ( os.str(), expected );
}


TEST( BoostBased, EncodeBinaryString )
{
     const unsigned char binaries[] = {
       0xb0, 0x68, 0x73, 0x1e, 0x75, 0xc0, 0xb1, 0x37, 0x3e, 0x1f,
       0xf5, 0xa4, 0xb4, 0x46, 0x8a, 0x2c, 0x1c, 0x29, 0x53, 0x31,
       0x20, 0xbe, 0x55, 0x86, 0xd9, 0x2d, 0xfc, 0x7c, 0x65, 0x15,
       0xac, 0xaa, 0xd8, 0xd6, 0x5e, 0x8b, 0x81, 0x9c, 0x9d, 0x6b,
       0x59, 0x29, 0x16, 0x8b, 0x5e, 0x29, 0xdf, 0x63, 0xce, 0xe5,
       0xbb, 0xc1, 0xd7, 0x39, 0xe6, 0xc7, 0xfd, 0xdd, 0xf8, 0xf5,
       0x0e, 0x2b, 0x2e, 0xdb, 0x4f, 0x68, 0xa7, 0x3e, 0x1e, 0x2c,
       0xbb, 0x5c, 0x74, 0x27, 0xf7, 0x88, 0x7a, 0xb5, 0xac, 0x0b,
       0x65, 0x15, 0xfe, 0x9d, 0x82, 0x03, 0x1c, 0xe2, 0x24, 0x56,
       0xac, 0x1d, 0x12, 0xe0, 0xfe, 0xee, 0x75, 0xfa, 0xc7, 0x19,
       0x78, 0xba, 0x56, 0xea, 0xc2, 0x4a, 0x9e, 0x43, 0x35, 0x7d,
       0xba, 0x93, 0x3f, 0x4d, 0x06, 0xd8, 0xda, 0xc0, 0x1c, 0xad,
       0xf2, 0x39, 0x8c, 0x61, 0xf3, 0xe0, 0x01, 0xc4
     };
     const auto n_binaries = sizeof(binaries) / sizeof(binaries[0]);

     const auto expected =
          "sGhzHnXAsTc+H/WktEaKLBwpUzEgvlWG2S38fGUVrKrY1l6LgZyda1k"
          "pFoteKd9jzuW7wdc55sf93fj1Disu209opz4eLLtcdCf3iHq1rAtlFf"
          "6dggMc4iRWrB0S4P7udfrHGXi6VurCSp5DNX26kz9NBtjawByt8jmMY"
          "fPgAcQ=";

     aux::binary_streambuf sbuf{ binaries, n_binaries };
     std::istream is{ &sbuf };
     std::ostringstream os;

     ASSERT_NO_THROW( base64::boost_based::encode( is, os ) );
     ASSERT_FALSE( os.str().empty() );
     ASSERT_EQ( os.str(), expected );
}


TEST( BoostBased, DecodeEmptyString )
{
     aux::inmem_streambuf sbuf{ "", 0 };
     std::istream is{ &sbuf };
     std::ostringstream os;

     ASSERT_NO_THROW( base64::boost_based::decode( is, os ) );
     ASSERT_TRUE( os.str().empty() );
}


TEST( BoostBased, DecodeTextString )
{
     const std::string base64 =
          "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaX"
          "Bpc2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIGluY2lkaWR1"
          "bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYSBhbGlxdWEuIFV0IGVuaW"
          "0gYWQgbWluaW0gdmVuaWFtLCBxdWlzIG5vc3RydWQgZXhlcmNpdGF0aW9u"
          "IHVsbGFtY28gbGFib3JpcyBuaXNpIHV0IGFsaXF1aXAgZXggZWEgY29tbW"
          "9kbyBjb25zZXF1YXQuIER1aXMgYXV0ZSBpcnVyZSBkb2xvciBpbiByZXBy"
          "ZWhlbmRlcml0IGluIHZvbHVwdGF0ZSB2ZWxpdCBlc3NlIGNpbGx1bSBkb2"
          "xvcmUgZXUgZnVnaWF0IG51bGxhIHBhcmlhdHVyLiBFeGNlcHRldXIgc2lu"
          "dCBvY2NhZWNhdCBjdXBpZGF0YXQgbm9uIHByb2lkZW50LCBzdW50IGluIG"
          "N1bHBhIHF1aSBvZmZpY2lhIGRlc2VydW50IG1vbGxpdCBhbmltIGlkIGVz"
          "dCBsYWJvcnVtLg==";
     const std::string expected =
          "Lorem ipsum dolor sit amet, consectetur adipiscing elit, "
          "sed do eiusmod tempor incididunt ut labore et dolore magna "
          "aliqua. Ut enim ad minim veniam, quis nostrud exercitation "
          "ullamco laboris nisi ut aliquip ex ea commodo consequat. "
          "Duis aute irure dolor in reprehenderit in voluptate velit "
          "esse cillum dolore eu fugiat nulla pariatur. Excepteur "
          "sint occaecat cupidatat non proident, sunt in culpa qui "
          "officia deserunt mollit anim id est laborum.";

     std::stringstream is;
     is << base64;
     std::ostringstream os;

     ASSERT_NO_THROW( base64::boost_based::decode( is, os ) );
     ASSERT_FALSE( os.str().empty() );
     ASSERT_EQ( os.str(), expected );
}


TEST( BoostBased, DecodeBinaryString )
{
     const auto base64 =
          "sGhzHnXAsTc+H/WktEaKLBwpUzEgvlWG2S38fGUVrKrY1l6LgZyda1k"
          "pFoteKd9jzuW7wdc55sf93fj1Disu209opz4eLLtcdCf3iHq1rAtlFf"
          "6dggMc4iRWrB0S4P7udfrHGXi6VurCSp5DNX26kz9NBtjawByt8jmMY"
          "fPgAcQ=";
     const unsigned char expected[] = {
       0xb0, 0x68, 0x73, 0x1e, 0x75, 0xc0, 0xb1, 0x37, 0x3e, 0x1f,
       0xf5, 0xa4, 0xb4, 0x46, 0x8a, 0x2c, 0x1c, 0x29, 0x53, 0x31,
       0x20, 0xbe, 0x55, 0x86, 0xd9, 0x2d, 0xfc, 0x7c, 0x65, 0x15,
       0xac, 0xaa, 0xd8, 0xd6, 0x5e, 0x8b, 0x81, 0x9c, 0x9d, 0x6b,
       0x59, 0x29, 0x16, 0x8b, 0x5e, 0x29, 0xdf, 0x63, 0xce, 0xe5,
       0xbb, 0xc1, 0xd7, 0x39, 0xe6, 0xc7, 0xfd, 0xdd, 0xf8, 0xf5,
       0x0e, 0x2b, 0x2e, 0xdb, 0x4f, 0x68, 0xa7, 0x3e, 0x1e, 0x2c,
       0xbb, 0x5c, 0x74, 0x27, 0xf7, 0x88, 0x7a, 0xb5, 0xac, 0x0b,
       0x65, 0x15, 0xfe, 0x9d, 0x82, 0x03, 0x1c, 0xe2, 0x24, 0x56,
       0xac, 0x1d, 0x12, 0xe0, 0xfe, 0xee, 0x75, 0xfa, 0xc7, 0x19,
       0x78, 0xba, 0x56, 0xea, 0xc2, 0x4a, 0x9e, 0x43, 0x35, 0x7d,
       0xba, 0x93, 0x3f, 0x4d, 0x06, 0xd8, 0xda, 0xc0, 0x1c, 0xad,
       0xf2, 0x39, 0x8c, 0x61, 0xf3, 0xe0, 0x01, 0xc4
     };
     const auto expected_len = sizeof(expected) / sizeof(expected[0]);

     std::stringstream is;
     is << base64;
     std::ostringstream os;

     ASSERT_NO_THROW( base64::boost_based::decode( is, os ) );
     const auto& result = os.str();
     ASSERT_FALSE( result.empty() );
     ASSERT_EQ( result.size(), expected_len );
     ASSERT_TRUE( std::memcmp( result.data(), expected, result.size() ) == 0 );
}
