#ifndef ZUU_CHAR_CLASS_HPP
#define ZUU_CHAR_CLASS_HPP

#include <type_traits>

#if (__cplusplus >= 201703L)
#define ZUU_INLINE_VAR inline
#else
#define ZUU_INLINE_VAR
#endif

namespace zuu {
namespace meta {

template <typename T> struct is_char_type : std::false_type {};

template <> struct is_char_type<char> : std::true_type {};

template <> struct is_char_type<wchar_t> : std::true_type {};

#if defined(__cpp_char8_t) || __cplusplus >= 202002L
template <> struct is_char_type<char8_t> : std::true_type {};
#endif

template <> struct is_char_type<char16_t> : std::true_type {};

template <> struct is_char_type<char32_t> : std::true_type {};

template <> struct is_char_type<unsigned char> : std::true_type {};

template <> struct is_char_type<signed char> : std::true_type {};

template <typename T>
ZUU_INLINE_VAR constexpr bool is_char_type_v = is_char_type<T>::value;

} // namespace meta
} // namespace zuu

#endif // ZUU_CHAR_CLASS_HPP