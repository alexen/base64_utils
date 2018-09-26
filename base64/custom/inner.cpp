//
// inner.cpp
//
// Created on: Sep 22, 2018
//     Author: alexen
//

#include <base64/custom/inner.h>

#include <stdexcept>
#include <boost/assert.hpp>
#include <boost/throw_exception.hpp>


namespace base64 {
namespace custom {
namespace inner {


namespace {


static constexpr char abc[] =
     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static inline unsigned char code( const char c ) noexcept
{
     switch( c )
     {
          case 'A': return  0; case 'B': return  1; case 'C': return  2; case 'D': return  3;
          case 'E': return  4; case 'F': return  5; case 'G': return  6; case 'H': return  7;
          case 'I': return  8; case 'J': return  9; case 'K': return 10; case 'L': return 11;
          case 'M': return 12; case 'N': return 13; case 'O': return 14; case 'P': return 15;
          case 'Q': return 16; case 'R': return 17; case 'S': return 18; case 'T': return 19;
          case 'U': return 20; case 'V': return 21; case 'W': return 22; case 'X': return 23;
          case 'Y': return 24; case 'Z': return 25; case 'a': return 26; case 'b': return 27;
          case 'c': return 28; case 'd': return 29; case 'e': return 30; case 'f': return 31;
          case 'g': return 32; case 'h': return 33; case 'i': return 34; case 'j': return 35;
          case 'k': return 36; case 'l': return 37; case 'm': return 38; case 'n': return 39;
          case 'o': return 40; case 'p': return 41; case 'q': return 42; case 'r': return 43;
          case 's': return 44; case 't': return 45; case 'u': return 46; case 'v': return 47;
          case 'w': return 48; case 'x': return 49; case 'y': return 50; case 'z': return 51;
          case '0': return 52; case '1': return 53; case '2': return 54; case '3': return 55;
          case '4': return 56; case '5': return 57; case '6': return 58; case '7': return 59;
          case '8': return 60; case '9': return 61; case '+': return 62; case '/': return 63;
          default: ;
     }
     return 0;
}

} // namespace {unnamed}



void encode_block( const unsigned char* in, const std::size_t len, char* out ) noexcept
{
     BOOST_ASSERT( 0 < len && len <= consts::INPUT_BLOCK_LEN );

     out[0] = abc[in[0] >> 2];
     out[1] = abc[((in[0] & 0x03) << 4) | (len > 1 ? ((in[1] & 0xf0) >> 4) : 0)];
     out[2] = (len > 1 ? abc[((in[1] & 0x0f) << 2) | (len > 2 ? ((in[2] & 0xc0) >> 6) : 0)] : '=');
     out[3] = (len > 2 ? abc[in[2] & 0x3f] : '=');
}


int decode_block( const char* in, unsigned char* out ) noexcept
{
     out[ 0 ] = (code(in[0]) << 2) | (code(in[1]) >> 4);
     out[ 1 ] = (code(in[1]) << 4) | (code(in[2]) >> 2);
     out[ 2 ] = (code(in[2]) << 6) | code(in[3]);
     return 3 - static_cast< int >(in[2] == '=') - static_cast< int >(in[3] == '=');
}


} // namespace inner
} // namespace custom
} // namespace base64
