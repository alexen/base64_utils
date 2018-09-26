//
// base64_inner_test.cpp
//
// Created on: Sep 26, 2018
//     Author: alexen
//

#include <gtest/gtest.h>
#include <base64/custom/inner.h>


TEST( CustomInner, EncodeShortString )
{
     const auto source = "String";
     const auto ucharptr = reinterpret_cast< const unsigned char* >( source );
     char output[ 4 ] = { 0 };

     ASSERT_NO_THROW( base64::custom::inner::encode_block( ucharptr, 1, output ) );
     ASSERT_EQ( "Uw==", std::string( output, sizeof( output ) ) );

     ASSERT_NO_THROW( base64::custom::inner::encode_block( ucharptr, 2, output ) );
     ASSERT_EQ( "U3Q=", std::string( output, sizeof( output ) ) );

     ASSERT_NO_THROW( base64::custom::inner::encode_block( ucharptr, 3, output ) );
     ASSERT_EQ( "U3Ry", std::string( output, sizeof( output ) ) );
}


TEST( CustomInner, EncodeShortBinary )
{
     const unsigned char binary[] = { 0x6d, 0x8f, 0x47 };
     char output[ 4 ] = { 0 };

     ASSERT_NO_THROW( base64::custom::inner::encode_block( binary, 1, output ) );
     ASSERT_EQ( "bQ==", std::string( output, sizeof( output ) ) );

     ASSERT_NO_THROW( base64::custom::inner::encode_block( binary, 2, output ) );
     ASSERT_EQ( "bY8=", std::string( output, sizeof( output ) ) );

     ASSERT_NO_THROW( base64::custom::inner::encode_block( binary, 3, output ) );
     ASSERT_EQ( "bY9H", std::string( output, sizeof( output ) ) );
}

