//
// base64.h
//
// Created on: Sep 21, 2018
//     Author: alexen
//

#pragma once

#include <iosfwd>


namespace base64 {
namespace boost_based {


void encode( std::istream& is, std::ostream& os );
void decode( std::istream& is, std::ostream& os );


} // namespace boost_based
} // namespace base64
