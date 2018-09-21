//
// main.cpp
//
// Created on: Sep 21, 2018
//     Author: alexen
//

#include <stdexcept>
#include <iostream>
#include <sstream>

#include <boost/exception/diagnostic_information.hpp>

#include <base64/boost_based/base64.h>


struct inmem_streambuf : std::streambuf {
     inmem_streambuf( const char* data, std::size_t len ) {
          setg(
               const_cast<char*>( data ),
               const_cast<char*>( data ),
               const_cast<char*>( data + len )
               );
     }
     inmem_streambuf( const std::string& str ) {
          setg(
               const_cast<char*>( str.data() ),
               const_cast<char*>( str.data() ),
               const_cast<char*>( str.data() + str.size() )
               );
     }
};


int main( int argc, char** argv )
{
     try
     {
          const std::string text = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.";
          const std::string expected = "TG9yZW0gaXBzdW0gZG9sb3Igc2l0IGFtZXQsIGNvbnNlY3RldHVyIGFkaXBpc2NpbmcgZWxpdCwgc2VkIGRvIGVpdXNtb2QgdGVtcG9yIGluY2lkaWR1bnQgdXQgbGFib3JlIGV0IGRvbG9yZSBtYWduYSBhbGlxdWEu";

          std::ostringstream base64_ostr;
          {
               inmem_streambuf sbuf{ text };
               std::istream is{ &sbuf };

               base64::boost_based::encode( is, base64_ostr );

               if( base64_ostr.str() == expected )
               {
                    std::cout << "Test passed!\n";
               }
               else
               {
                    std::cout << "Test FAILED!\n"
                         << "  expected: " << expected << '\n'
                         << "  actual  : " << base64_ostr.str() << '\n';
               }
          }
          {
               inmem_streambuf sbuf{ expected };
               std::istream is{ &sbuf };
               std::ostringstream text_ostr;

               base64::boost_based::decode( is, text_ostr );

               if( text_ostr.str() == text )
               {
                    std::cout << "Test passed!\n";
               }
               else
               {
                    std::cout << "Test FAILED!\n"
                         << "  expected: " << text << '\n'
                         << "  actual  : " << text_ostr.str() << '\n';
               }
          }
     }
     catch( const std::exception& e )
     {
          std::cerr << "exception: " << boost::diagnostic_information( e ) << '\n';
          return 1;
     }
     return 0;
}
