#include "nexus_core.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#endif // __clang__
#endif // __GNUC__

namespace rust {
inline namespace cxxbridge1 {
// #include "rust/cxx.h"

#ifndef CXXBRIDGE1_IS_COMPLETE
#define CXXBRIDGE1_IS_COMPLETE
namespace detail {
namespace {
template <typename T, typename = std::size_t>
struct is_complete : std::false_type {};
template <typename T>
struct is_complete<T, decltype(sizeof(T))> : std::true_type {};
} // namespace
} // namespace detail
#endif // CXXBRIDGE1_IS_COMPLETE

namespace {
template <bool> struct deleter_if {
  template <typename T> void operator()(T *) {}
};
template <> struct deleter_if<true> {
  template <typename T> void operator()(T *ptr) { ptr->~T(); }
};
} // namespace
} // namespace cxxbridge1
} // namespace rust

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

extern "C" {
::logispeed::NexusCore *logispeed$cxxbridge1$194$criar_nexus() noexcept {
  ::std::unique_ptr<::logispeed::NexusCore> (*criar_nexus$)() = ::logispeed::criar_nexus;
  return criar_nexus$().release();
}

void logispeed$cxxbridge1$194$NexusCore$processar_pacote_assincrono(::logispeed::NexusCore const &self, ::std::int32_t id_satelite) noexcept {
  void (::logispeed::NexusCore::*processar_pacote_assincrono$)(::std::int32_t) const = &::logispeed::NexusCore::processar_pacote_assincrono;
  (self.*processar_pacote_assincrono$)(id_satelite);
}

::std::int64_t logispeed$cxxbridge1$194$NexusCore$obter_total_processado(::logispeed::NexusCore const &self) noexcept {
  ::std::int64_t (::logispeed::NexusCore::*obter_total_processado$)() const = &::logispeed::NexusCore::obter_total_processado;
  return (self.*obter_total_processado$)();
}

void logispeed$cxxbridge1$194$NexusCore$capturar_dados_hardware(::logispeed::NexusCore const &self, ::logispeed::RawTelemetria *return$) noexcept {
  ::logispeed::RawTelemetria (::logispeed::NexusCore::*capturar_dados_hardware$)() const = &::logispeed::NexusCore::capturar_dados_hardware;
  new (return$) ::logispeed::RawTelemetria((self.*capturar_dados_hardware$)());
}
} // extern "C"
} // namespace logispeed

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::logispeed::NexusCore>::type>::value, "definition of `::logispeed::NexusCore` is required");
static_assert(sizeof(::std::unique_ptr<::logispeed::NexusCore>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::logispeed::NexusCore>) == alignof(void *), "");
void cxxbridge1$unique_ptr$logispeed$NexusCore$null(::std::unique_ptr<::logispeed::NexusCore> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::logispeed::NexusCore>();
}
void cxxbridge1$unique_ptr$logispeed$NexusCore$raw(::std::unique_ptr<::logispeed::NexusCore> *ptr, ::std::unique_ptr<::logispeed::NexusCore>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::logispeed::NexusCore>(raw);
}
::std::unique_ptr<::logispeed::NexusCore>::element_type const *cxxbridge1$unique_ptr$logispeed$NexusCore$get(::std::unique_ptr<::logispeed::NexusCore> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::logispeed::NexusCore>::pointer cxxbridge1$unique_ptr$logispeed$NexusCore$release(::std::unique_ptr<::logispeed::NexusCore> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$logispeed$NexusCore$drop(::std::unique_ptr<::logispeed::NexusCore> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::logispeed::NexusCore>::value>{}(ptr);
}
} // extern "C"
