#include "ffi-avancado/include/motor_rota.h"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>
#include <string>
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

struct unsafe_bitcopy_t;

#ifndef CXXBRIDGE1_RUST_STRING
#define CXXBRIDGE1_RUST_STRING
class String final {
public:
  String() noexcept;
  String(const String &) noexcept;
  String(String &&) noexcept;
  ~String() noexcept;

  String(const std::string &);
  String(const char *);
  String(const char *, std::size_t);
  String(const char16_t *);
  String(const char16_t *, std::size_t);
#ifdef __cpp_char8_t
  String(const char8_t *s);
  String(const char8_t *s, std::size_t len);
#endif

  static String lossy(const std::string &) noexcept;
  static String lossy(const char *) noexcept;
  static String lossy(const char *, std::size_t) noexcept;
  static String lossy(const char16_t *) noexcept;
  static String lossy(const char16_t *, std::size_t) noexcept;

  String &operator=(const String &) & noexcept;
  String &operator=(String &&) & noexcept;

  explicit operator std::string() const;

  const char *data() const noexcept;
  std::size_t size() const noexcept;
  std::size_t length() const noexcept;
  bool empty() const noexcept;

  const char *c_str() noexcept;

  std::size_t capacity() const noexcept;
  void reserve(size_t new_cap) noexcept;

  using iterator = char *;
  iterator begin() noexcept;
  iterator end() noexcept;

  using const_iterator = const char *;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool operator==(const String &) const noexcept;
  bool operator!=(const String &) const noexcept;
  bool operator<(const String &) const noexcept;
  bool operator<=(const String &) const noexcept;
  bool operator>(const String &) const noexcept;
  bool operator>=(const String &) const noexcept;

  void swap(String &) noexcept;

  String(unsafe_bitcopy_t, const String &) noexcept;

private:
  struct lossy_t;
  String(lossy_t, const char *, std::size_t) noexcept;
  String(lossy_t, const char16_t *, std::size_t) noexcept;
  friend void swap(String &lhs, String &rhs) noexcept { lhs.swap(rhs); }

  std::array<std::uintptr_t, 3> repr;
};
#endif // CXXBRIDGE1_RUST_STRING

#ifndef CXXBRIDGE1_RUST_BITCOPY_T
#define CXXBRIDGE1_RUST_BITCOPY_T
struct unsafe_bitcopy_t final {
  explicit unsafe_bitcopy_t() = default;
};
#endif // CXXBRIDGE1_RUST_BITCOPY_T

#ifndef CXXBRIDGE1_RUST_BITCOPY
#define CXXBRIDGE1_RUST_BITCOPY
constexpr unsafe_bitcopy_t unsafe_bitcopy{};
#endif // CXXBRIDGE1_RUST_BITCOPY

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

namespace logispeed {
  using MotorRota = ::logispeed::MotorRota;
}

namespace logispeed {
extern "C" {
::logispeed::MotorRota *logispeed$cxxbridge1$194$novo_motor(::rust::String const *config) noexcept {
  ::std::unique_ptr<::logispeed::MotorRota> (*novo_motor$)(::rust::String) = ::logispeed::novo_motor;
  return novo_motor$(::rust::String(::rust::unsafe_bitcopy, *config)).release();
}

void logispeed$cxxbridge1$194$MotorRota$calcular_melhor_rota(::logispeed::MotorRota const &self, ::rust::String const *origem, ::rust::String const *destino, ::rust::String *return$) noexcept {
  ::rust::String (::logispeed::MotorRota::*calcular_melhor_rota$)(::rust::String, ::rust::String) const = &::logispeed::MotorRota::calcular_melhor_rota;
  new (return$) ::rust::String((self.*calcular_melhor_rota$)(::rust::String(::rust::unsafe_bitcopy, *origem), ::rust::String(::rust::unsafe_bitcopy, *destino)));
}

double logispeed$cxxbridge1$194$MotorRota$obter_distancia(::logispeed::MotorRota const &self) noexcept {
  double (::logispeed::MotorRota::*obter_distancia$)() const = &::logispeed::MotorRota::obter_distancia;
  return (self.*obter_distancia$)();
}
} // extern "C"
} // namespace logispeed

extern "C" {
static_assert(::rust::detail::is_complete<::std::remove_extent<::logispeed::MotorRota>::type>::value, "definition of `::logispeed::MotorRota` is required");
static_assert(sizeof(::std::unique_ptr<::logispeed::MotorRota>) == sizeof(void *), "");
static_assert(alignof(::std::unique_ptr<::logispeed::MotorRota>) == alignof(void *), "");
void cxxbridge1$unique_ptr$logispeed$MotorRota$null(::std::unique_ptr<::logispeed::MotorRota> *ptr) noexcept {
  ::new (ptr) ::std::unique_ptr<::logispeed::MotorRota>();
}
void cxxbridge1$unique_ptr$logispeed$MotorRota$raw(::std::unique_ptr<::logispeed::MotorRota> *ptr, ::std::unique_ptr<::logispeed::MotorRota>::pointer raw) noexcept {
  ::new (ptr) ::std::unique_ptr<::logispeed::MotorRota>(raw);
}
::std::unique_ptr<::logispeed::MotorRota>::element_type const *cxxbridge1$unique_ptr$logispeed$MotorRota$get(::std::unique_ptr<::logispeed::MotorRota> const &ptr) noexcept {
  return ptr.get();
}
::std::unique_ptr<::logispeed::MotorRota>::pointer cxxbridge1$unique_ptr$logispeed$MotorRota$release(::std::unique_ptr<::logispeed::MotorRota> &ptr) noexcept {
  return ptr.release();
}
void cxxbridge1$unique_ptr$logispeed$MotorRota$drop(::std::unique_ptr<::logispeed::MotorRota> *ptr) noexcept {
  ::rust::deleter_if<::rust::detail::is_complete<::logispeed::MotorRota>::value>{}(ptr);
}
} // extern "C"
