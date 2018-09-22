//
// base64.cpp
//
// Created on: Sep 22, 2018
//     Author: alexen
//

#include <base64/custom/base64.h>

#include <stdexcept>
#include <iostream>
#include <boost/throw_exception.hpp>

#include <base64/custom/inner.h>


namespace base64 {
namespace custom {


void encode( std::istream& is, std::ostream& os )
{
     unsigned char inbuf[ inner::consts::INPUT_BLOCK_LEN ];
     char outbuf[ inner::consts::OUTPUT_BLOCK_LEN ];

     std::streamsize read = 0;
     while( (read = is.readsome( reinterpret_cast< char* >( inbuf ), sizeof( inbuf ) )) > 0 )
     {
          inner::encode_block( inbuf, read, outbuf );
          os.write( outbuf, sizeof( outbuf ) );
     }
}


void decode( std::istream& is, std::ostream& os )
{
     BOOST_THROW_EXCEPTION( std::runtime_error{ "not implemented" } );
}


} // namespace custom
} // namespace base64
