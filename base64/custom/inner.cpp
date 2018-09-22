//
// inner.cpp
//
// Created on: Sep 22, 2018
//     Author: alexen
//

#include <base64/custom/inner.h>

#include <boost/assert.hpp>


namespace base64 {
namespace custom {
namespace inner {


void encode_block( const unsigned char* in, const std::size_t len, char* out )
{
     BOOST_ASSERT( 0 < len && len <= consts::INPUT_BLOCK_LEN );

     static constexpr char abc[] =
          "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

     out[0] = abc[in[0] >> 2];
     out[1] = abc[((in[0] & 0x03) << 4) | (len > 1 ? ((in[1] & 0xf0) >> 4) : 0)];
     out[2] = (len > 1 ? abc[((in[1] & 0x0f) << 2) | (len > 2 ? ((in[2] & 0xc0) >> 6) : 0)] : '=');
     out[3] = (len > 2 ? abc[in[2] & 0x3f] : '=');
}


} // namespace inner
} // namespace custom
} // namespace base64
