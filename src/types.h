#pragma once

#include <cstddef>
#include <cstdint>

using u64 = uint64_t;
using u32 = uint32_t;
using u16 = uint16_t;
using u8 = uint8_t;
using i64 = int64_t;
using i32 = int32_t;
using i16 = int16_t;
using i8 = int8_t;
using f64 = double;
using f32 = float;

using usize = size_t;
using isize = ptrdiff_t;

static constexpr u64 KiB = 1024;
static constexpr u64 MiB = KiB * KiB;
static constexpr u64 GiB = KiB * KiB * KiB;
static constexpr u64 TiB = KiB * KiB * KiB * KiB;
static constexpr u64 PiB = KiB * KiB * KiB * KiB * KiB;
static constexpr u64 EiB = KiB * KiB * KiB * KiB * KiB * KiB;

namespace types {

} // namespace types
