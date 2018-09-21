//
// base64.cpp
//
// Created on: Sep 21, 2018
//     Author: alexen
//

#include <base64/boost_based/base64.h>

#include <iterator>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>


namespace base64 {
namespace boost_based {

namespace {

using to_base64 =
     boost::archive::iterators::base64_from_binary<
          boost::archive::iterators::transform_width<
               std::istream_iterator<char>,
               6,
               8
          >
     >;

using from_base64 =
     boost::archive::iterators::transform_width<
          boost::archive::iterators::binary_from_base64<
               std::istream_iterator<char>
          >,
          8,
          6
     >;

} // namespace {unnamed}



void encode( std::istream& is, std::ostream& os )
{
     std::copy(
             to_base64( std::istream_iterator<char>{ is >> std::noskipws } ),
             to_base64( std::istream_iterator<char>{} ),
             std::ostream_iterator<char>{ os }
         );
}


void decode( std::istream& is, std::ostream& os )
{
     std::copy(
             from_base64( std::istream_iterator<char>{ is } ),
             from_base64( std::istream_iterator<char>{} ),
             std::ostream_iterator<char>{ os }
         );
}


} // namespace boost_based
} // namespace base64
