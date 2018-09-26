//
// inner.h
//
// Created on: Sep 22, 2018
//     Author: alexen
//

#pragma once

#include <cstddef>


namespace base64 {
namespace custom {
namespace inner {

namespace consts {

constexpr std::size_t INPUT_BLOCK_LEN = 3;
constexpr std::size_t OUTPUT_BLOCK_LEN = 4;

} // namespace consts



void encode_block( const unsigned char* in, const std::size_t len, char* out ) noexcept;

int decode_block( const char* in, unsigned char* out ) noexcept;


} // namespace inner
} // namespace custom
} // namespace base64
