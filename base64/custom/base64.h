//
// base64.h
//
// Created on: Sep 22, 2018
//     Author: alexen
//

#pragma once

#include <iosfwd>


namespace base64 {
namespace custom {


void encode( std::istream& is, std::ostream& os );
void decode( std::istream& is, std::ostream& os );


} // namespace custom
} // namespace base64
