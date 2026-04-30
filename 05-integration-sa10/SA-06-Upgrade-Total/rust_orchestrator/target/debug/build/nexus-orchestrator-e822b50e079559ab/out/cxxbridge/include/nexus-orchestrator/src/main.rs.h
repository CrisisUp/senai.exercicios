#pragma once
#include "nexus_core.h"
#include <cstdint>
#include <memory>
#include <type_traits>

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__

#if __cplusplus >= 201402L
#define CXX_DEFAULT_VALUE(value) = value
#else
#define CXX_DEFAULT_VALUE(value)
#endif

namespace logispeed {
  struct RawTelemetria;
  using NexusCore = ::logispeed::NexusCore;
}

namespace logispeed {
#ifndef CXXBRIDGE1_STRUCT_logispeed$RawTelemetria
#define CXXBRIDGE1_STRUCT_logispeed$RawTelemetria
struct RawTelemetria final {
  ::std::int32_t id CXX_DEFAULT_VALUE(0);
  double lat CXX_DEFAULT_VALUE(0);
  double lon CXX_DEFAULT_VALUE(0);
  double velocidade CXX_DEFAULT_VALUE(0);
  double combustivel CXX_DEFAULT_VALUE(0);

  using IsRelocatable = ::std::true_type;
};
#endif // CXXBRIDGE1_STRUCT_logispeed$RawTelemetria
} // namespace logispeed

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__
