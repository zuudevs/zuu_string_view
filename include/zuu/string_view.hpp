#ifndef ZUU_STRING_VIEW_HPP
#define ZUU_STRING_VIEW_HPP

#include <zuu/char_class.hpp>
#include <cstring>
#include <ostream>
#include <string>
#include <type_traits>

#if (__cplusplus >= 201703L)
#include <string_view>
#elif (__cplusplus >= 202002L)
#include <bit>
#include <string_view>
#endif

namespace zuu {
template <typename CharT,
          typename = std::enable_if_t<zuu::meta::is_char_type_v<CharT>>>
struct basic_string_view {
public:
  using char_type = CharT;
  using size_type = unsigned int;
  using pointer_type = const char_type *;
  static constexpr size_type npos = ~size_type{};

  constexpr basic_string_view() noexcept = default;
  constexpr basic_string_view(const basic_string_view &) noexcept = default;
  constexpr basic_string_view &
  operator=(const basic_string_view &) noexcept = default;
  constexpr basic_string_view(basic_string_view &&) noexcept = default;
  constexpr basic_string_view &
  operator=(basic_string_view &&) noexcept = default;
  ~basic_string_view() = default;

  template <size_t N>
  constexpr basic_string_view(const CharT (&arr)[N]) noexcept
      : data_(arr), length_(N - 1) {}

  constexpr basic_string_view(pointer_type data, size_type length) noexcept
      : data_(data), length_(length) {}

  constexpr basic_string_view(pointer_type begin, pointer_type end) noexcept
      : data_(begin), length_(static_cast<size_type>(end - begin)) {}

  constexpr basic_string_view(const std::string &str) noexcept
      : data_(str.data()), length_(static_cast<size_type>(str.length())) {}

  constexpr pointer_type data() const noexcept { return data_; }
  constexpr size_type size() const noexcept { return length_; }
  constexpr bool empty() const noexcept { return length_ == 0; }

  operator std::basic_string<CharT>() const {
    return std::basic_string<CharT>{data_, length_};
  }

#if defined(__cpp_lib_string_view) || (__cplusplus >= 201703L)
  operator std::basic_string_view<CharT>() const noexcept {
    return std::basic_string_view<CharT>{data_, length_};
  }
#endif

  constexpr size_type find(CharT ch, size_type pos = 0) const noexcept {
    if (pos >= length_) {
      return npos;
    }

    auto ptr = data_ + pos;
    auto remaining = length_ - pos;

    if (!is_constant_eval_() && sizeof(CharT) == 1 && remaining >= tape_size) {
      uint64_t pattern = make_tape(ch);
      const CharT *const swar_end = data_ + length_ - tape_size;

      while (ptr <= swar_end) {
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        uint64_t xored = block ^ pattern;
        uint64_t match = ((xored - lsb64) & ~xored & msb64);

        if (match != 0) {
          unsigned shift = count_trailing_zeros(match) >> 3;
          return (ptr - data_) + shift;
        }
        ptr += tape_size;
      }
    }

    for (size_type i = (ptr - data_); i < length_; ++i) {
      if (data_[i] == ch) {
        return i;
      }
    }

    return npos;
  }

  constexpr size_type find(const CharT *str, size_type pos,
                           size_type count) const noexcept {
    if (!str) {
      return npos;
    }
    return find_substring(str, count, pos);
  }

  constexpr size_type find(const CharT *str, size_type pos = 0) const noexcept {
    if (!str) {
      return npos;
    }
    return find_substring(str, c_strlen(str), pos);
  }

  constexpr size_type find(basic_string_view str,
                           size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_substring(str.data(), static_cast<size_type>(str.size()), pos);
  }

  constexpr size_type find(const std::string &str,
                           size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_substring(str.data(), static_cast<size_type>(str.length()),
                          pos);
  }

  constexpr size_type rfind(CharT ch, size_type pos = npos) const noexcept {
    if (length_ == 0) {
      return npos;
    }
    pos = pos < length_ ? pos : length_ - 1;

    if (!is_constant_eval_() && sizeof(CharT) == 1) {
      uint64_t pattern = make_tape(ch);
      while (pos >= tape_size - 1) {
        const CharT *ptr = data_ + pos - (tape_size - 1);
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        uint64_t xored = block ^ pattern;
        uint64_t match = ((xored - lsb64) & ~xored & msb64);

        if (match != 0) {
          unsigned shift = 63 - count_leading_zeros(match);
          return (ptr - data_) + (shift >> 3);
        }
        pos -= tape_size;
      }
    }

    for (size_type i = pos + 1; i > 0; --i) {
      if (data_[i - 1] == ch)
        return i - 1;
    }
    return npos;
  }

  constexpr size_type rfind(const CharT *str, size_type pos,
                            size_type count) const noexcept {
    if (!str) {
      return npos;
    }
    return rfind_substring(str, count, pos);
  }

  constexpr size_type rfind(const CharT *str,
                            size_type pos = npos) const noexcept {
    if (!str) {
      return npos;
    }
    return rfind_substring(str, c_strlen(str), pos);
  }

  constexpr size_type rfind(basic_string_view str,
                            size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return rfind_substring(str.data(), str.size(), pos);
  }

  constexpr size_type rfind(const std::string &str,
                            size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return rfind_substring(str.data(), static_cast<size_type>(str.length()),
                           pos);
  }

  constexpr size_type find_first_of(CharT ch,
                                    size_type pos = 0) const noexcept {
    return find(ch, pos);
  }

  constexpr size_type find_first_of(const CharT *str, size_type pos,
                                    size_type count) const noexcept {
    if (!str) {
      return npos;
    }
    return find_first_of_impl(str, count, pos);
  }

  constexpr size_type find_first_of(const CharT *str,
                                    size_type pos = 0) const noexcept {
    if (!str) {
      return npos;
    }
    return find_first_of_impl(str, c_strlen(str), pos);
  }

  constexpr size_type find_first_of(basic_string_view str,
                                    size_type pos = 0) const noexcept {
    return find_first_of_impl(str.data(), static_cast<size_type>(str.size()),
                              pos);
  }

  constexpr size_type find_first_of(const std::string &str,
                                    size_type pos = 0) const noexcept {
    return find_first_of_impl(str.data(), static_cast<size_type>(str.length()),
                              pos);
  }

  constexpr size_type find_last_of(CharT ch,
                                   size_type pos = npos) const noexcept {
    return rfind(ch, pos);
  }

  constexpr size_type find_last_of(const CharT *str, size_type pos,
                                   size_type count) const noexcept {
    if (!str) {
      return npos;
    }
    return find_last_of_impl(str, count, pos);
  }

  constexpr size_type find_last_of(const CharT *str,
                                   size_type pos = npos) const noexcept {
    if (!str) {
      return npos;
    }
    return find_last_of_impl(str, c_strlen(str), pos);
  }

  constexpr size_type find_last_of(basic_string_view str,
                                   size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_last_of_impl(str.data(), str.size(), pos);
  }

  constexpr size_type find_last_of(const std::string &str,
                                   size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_last_of_impl(str.data(), static_cast<size_type>(str.length()),
                             pos);
  }

  constexpr size_type find_first_not_of(CharT ch,
                                        size_type pos = 0) const noexcept {
    return find_first_not_of_impl(&ch, 1, pos);
  }

  constexpr size_type find_first_not_of(const CharT *str, size_type pos,
                                        size_type count) const noexcept {
    if (!str) {
      return npos;
    }
    return find_first_not_of_impl(str, count, pos);
  }

  constexpr size_type find_first_not_of(const CharT *str,
                                        size_type pos = 0) const noexcept {
    if (!str) {
      return npos;
    }
    return find_first_not_of_impl(str, c_strlen(str), pos);
  }

  constexpr size_type find_first_not_of(basic_string_view str,
                                        size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_first_not_of_impl(str.data(), str.size(), pos);
  }

  constexpr size_type find_first_not_of(const std::string &str,
                                        size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_first_not_of_impl(str.data(),
                                  static_cast<size_type>(str.length()), pos);
  }

  constexpr size_type find_last_not_of(CharT ch,
                                       size_type pos = npos) const noexcept {
    return find_last_not_of_impl(&ch, 1, pos);
  }

  constexpr size_type find_last_not_of(const CharT *str, size_type pos,
                                       size_type count) const noexcept {
    if (!str) {
      return npos;
    }
    return find_last_not_of_impl(str, count, pos);
  }

  constexpr size_type find_last_not_of(const CharT *str,
                                       size_type pos = npos) const noexcept {
    if (!str) {
      return npos;
    }
    return find_last_not_of_impl(str, c_strlen(str), pos);
  }

  constexpr size_type find_last_not_of(basic_string_view str,
                                       size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_last_not_of_impl(str.data(), str.size(), pos);
  }

  constexpr size_type find_last_not_of(const std::string &str,
                                       size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_last_not_of_impl(str.data(),
                                 static_cast<size_type>(str.length()), pos);
  }

  constexpr basic_string_view substr(size_type pos,
                                     size_type count) const noexcept {
    if (pos > length_) {
      return basic_string_view(data_ + length_, size_type{});
    }

    size_type rcount = count;
    if (count == npos || pos + count > length_) {
      rcount = length_ - pos;
    }

    return basic_string_view(data_ + pos, rcount);
  }

#if (__cplusplus >= 201703L)
  constexpr size_type find(std::string_view str,
                           size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_substring(str.data(), static_cast<size_type>(str.size()), pos);
  }

  constexpr size_type rfind(std::string_view str,
                            size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return rfind_substring(str.data(), static_cast<size_type>(str.size()), pos);
  }

  constexpr size_type find_first_of(std::string_view str,
                                    size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_first_of_impl(str.data(), static_cast<size_type>(str.size()),
                              pos);
  }

  constexpr size_type find_last_of(std::string_view str,
                                   size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_last_of_impl(str.data(), static_cast<size_type>(str.size()),
                             pos);
  }

  constexpr size_type find_first_not_of(std::string_view str,
                                        size_type pos = 0) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_first_not_of_impl(str.data(),
                                  static_cast<size_type>(str.size()), pos);
  }

  constexpr size_type find_last_not_of(std::string_view str,
                                       size_type pos = npos) const noexcept {
    if (str.empty()) {
      return npos;
    }
    return find_last_not_of_impl(str.data(), static_cast<size_type>(str.size()),
                                 pos);
  }
#endif

  friend std::ostream &operator<<(std::ostream &out,
                                  const basic_string_view &data) {
    if (data.data_ && data.length_ > 0) {
      out.write(data.data_, static_cast<std::streamsize>(data.length_));
    }
    return out;
  }

private:
  using tape_type = uint64_t;
  static constexpr tape_type lsb64 = 0x0101010101010101ULL;
  static constexpr tape_type msb64 = 0x8080808080808080ULL;
  static constexpr uint8_t tape_size = sizeof(tape_type);

  pointer_type data_;
  size_type length_;

  static constexpr bool is_constant_eval_() noexcept {
#if (__cplusplus >= 202002L)
    return std::is_constant_evaluated();
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_is_constant_evaluated();
#else
    return false;
#endif
  }

  static constexpr unsigned count_trailing_zeros(uint64_t x) noexcept {
#if (__cplusplus >= 202002L)
    return std::countr_zero(x);
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_ctzll(x);
#else
    return 0;
#endif
  }

  static constexpr unsigned count_leading_zeros(uint64_t x) noexcept {
#if (__cplusplus >= 202002L)
    return std::countl_zero(x);
#elif defined(__GNUC__) || defined(__clang__)
    return __builtin_clzll(x);
#else
    return 0;
#endif
  }

  static constexpr size_type c_strlen(const CharT *str) noexcept {
    size_type len = 0;
    while (str[len] != CharT{})
      ++len;
    return len;
  }

  inline constexpr tape_type make_tape(CharT ch) const noexcept {
    tape_type tape{static_cast<uint8_t>(ch)};
    tape |= tape << 8;
    tape |= tape << 16;
    tape |= tape << 32;
    return tape;
  }

  constexpr size_type find_substring(const CharT *str, size_type str_len,
                                     size_type pos) const noexcept {
    if (str_len == 0)
      return pos <= length_ ? pos : npos;
    if (pos >= length_ || str_len > length_ - pos)
      return npos;
    if (str_len == 1)
      return find(str[0], pos);

    CharT first_ch = str[0];
    CharT last_ch = str[str_len - 1];
    auto ptr = data_ + pos;

    if (!is_constant_eval_() && sizeof(CharT) == 1 &&
        length_ - pos >= tape_size) {
      tape_type pattern_first = make_tape(first_ch);

      const CharT *const swar_end = data_ + length_ - tape_size;

      while (ptr <= swar_end) {
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        uint64_t xored = block ^ pattern_first;
        uint64_t match = ((xored - lsb64) & ~xored & msb64);

        while (match != 0) {
          unsigned shift = count_trailing_zeros(match) >> 3;
          const CharT *candidate_ptr = ptr + shift;

          if (candidate_ptr > data_ + length_ - str_len)
            break;

          if (candidate_ptr[str_len - 1] == last_ch) {
            bool matched = true;
            for (size_type i = 1; i < str_len - 1; ++i) {
              if (candidate_ptr[i] != str[i]) {
                matched = false;
                break;
              }
            }
            if (matched)
              return static_cast<size_type>(candidate_ptr - data_);
          }
          match &= match - 1;
        }
        ptr += tape_size;
      }
    }

    for (size_type i = static_cast<size_type>(ptr - data_);
         i <= length_ - str_len; ++i) {
      bool matched = true;
      for (size_type j = 0; j < str_len; ++j) {
        if (data_[i + j] != str[j]) {
          matched = false;
          break;
        }
      }
      if (matched)
        return i;
    }

    return npos;
  }

  constexpr size_type rfind_substring(const CharT *str, size_type str_len,
                                      size_type pos) const noexcept {
    if (str_len == 0) {
      return pos <= length_ ? pos : length_;
    }

    if (str_len > length_) {
      return npos;
    }

    pos = pos < length_ - str_len ? pos : length_ - str_len;

    if (str_len == 1) {
      return rfind(str[0], pos);
    }

    if (!is_constant_eval_() && sizeof(CharT) == 1) {
      CharT first_ch = str[0];
      tape_type pattern_first = make_tape(first_ch);

      while (pos >= tape_size - 1) {
        const CharT *ptr = data_ + pos - (tape_size - 1);
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        uint64_t xored = block ^ pattern_first;
        uint64_t match = ((xored - lsb64) & ~xored & msb64);

        while (match != 0) {
          unsigned shift = 63 - count_leading_zeros(match);
          uint64_t bit_mask = 1ULL << shift;
          size_type candidate_pos = (ptr - data_) + (shift >> 3);

          if (candidate_pos <= pos) {
            bool matched = true;
            for (size_type i = 1; i < str_len; ++i) {
              if (data_[candidate_pos + i] != str[i]) {
                matched = false;
                break;
              }
            }

            if (matched) {
              return candidate_pos;
            }
          }

          match &= ~bit_mask;
        }

        if (pos < tape_size) {
          break;
        }

        pos -= tape_size;
      }
    }

    for (size_type i = pos + 1; i > 0; --i) {
      bool matched = true;
      for (size_type j = 0; j < str_len; ++j) {
        if (data_[i - 1 + j] != str[j]) {
          matched = false;
          break;
        }
      }

      if (matched) {
        return i - 1;
      }
    }

    return npos;
  }

  constexpr size_type find_first_of_impl(const CharT *str, size_type str_len,
                                         size_type pos) const noexcept {
    if (pos >= length_ || str_len == 0)
      return npos;
    if (str_len == 1)
      return find(str[0], pos);

    auto ptr = data_ + pos;

    if (!is_constant_eval_() && sizeof(CharT) == 1 &&
        length_ - pos >= tape_size) {
      const CharT *const swar_end = data_ + length_ - tape_size;
      tape_type tapes[tape_size]{};
      size_type tape_count = str_len < tape_size ? str_len : tape_size;
      for (size_type i = 0; i < tape_count; ++i)
        tapes[i] = make_tape(str[i]);

      while (ptr <= swar_end) {
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        if (str_len <= 8) {
          uint64_t match = 0;
          for (size_type i = 0; i < str_len; ++i) {
            uint64_t xored = block ^ tapes[i];
            match |= ((xored - lsb64) & ~xored & msb64);
          }
          if (match != 0) {
            unsigned shift = count_trailing_zeros(match) >> 3;
            return (ptr - data_) + shift;
          }
        } else {
          uint64_t lookup[4] = {0};
          for (size_type i = 0; i < str_len; ++i) {
            uint8_t c = static_cast<uint8_t>(str[i]);
            lookup[c >> 6] |= (1ULL << (c & 63));
          }
          for (size_type i = 0; i < tape_size; ++i) {
            uint8_t c = static_cast<uint8_t>(ptr[i]);
            if (lookup[c >> 6] & (1ULL << (c & 63))) {
              return (ptr - data_) + i;
            }
          }
        }
        ptr += tape_size;
      }
    }

    for (size_type i = (ptr - data_); i < length_; ++i) {
      for (size_type j = 0; j < str_len; ++j) {
        if (data_[i] == str[j])
          return i;
      }
    }
    return npos;
  }

  constexpr size_type find_first_not_of_impl(const CharT *str,
                                             size_type str_len,
                                             size_type pos) const noexcept {
    if (pos >= length_)
      return npos;
    if (str_len == 0)
      return pos;

    auto ptr = data_ + pos;

    if (!is_constant_eval_() && sizeof(CharT) == 1 &&
        length_ - pos >= tape_size) {
      const CharT *const swar_end = data_ + length_ - tape_size;
      tape_type tapes[tape_size]{};
      size_type tape_count = str_len < tape_size ? str_len : tape_size;
      for (size_type i = 0; i < tape_count; ++i)
        tapes[i] = make_tape(str[i]);

      while (ptr <= swar_end) {
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        if (str_len <= 8) {
          uint64_t match = 0;
          for (size_type i = 0; i < str_len; ++i) {
            uint64_t xored = block ^ tapes[i];
            match |= ((xored - lsb64) & ~xored & msb64);
          }
          uint64_t not_match = ~match & msb64;
          if (not_match != 0) {
            unsigned shift = count_trailing_zeros(not_match) >> 3;
            return (ptr - data_) + shift;
          }
        } else {
          uint64_t lookup[4] = {0};
          for (size_type i = 0; i < str_len; ++i) {
            uint8_t c = static_cast<uint8_t>(str[i]);
            lookup[c >> 6] |= (1ULL << (c & 63));
          }
          for (size_type i = 0; i < tape_size; ++i) {
            uint8_t c = static_cast<uint8_t>(ptr[i]);
            if (!(lookup[c >> 6] & (1ULL << (c & 63)))) {
              return (ptr - data_) + i;
            }
          }
        }
        ptr += tape_size;
      }
    }

    for (size_type i = (ptr - data_); i < length_; ++i) {
      bool found = false;
      for (size_type j = 0; j < str_len; ++j) {
        if (data_[i] == str[j]) {
          found = true;
          break;
        }
      }
      if (!found)
        return i;
    }
    return npos;
  }

  constexpr size_type find_last_of_impl(const CharT *str, size_type str_len,
                                        size_type pos) const noexcept {
    if (length_ == 0 || str_len == 0)
      return npos;
    pos = pos < length_ ? pos : length_ - 1;

    if (!is_constant_eval_() && sizeof(CharT) == 1) {
      tape_type tapes[tape_size]{};
      size_type tape_count = str_len < tape_size ? str_len : tape_size;
      for (size_type i = 0; i < tape_count; ++i)
        tapes[i] = make_tape(str[i]);

      while (pos >= tape_size - 1) {
        const CharT *ptr = data_ + pos - (tape_size - 1);
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        if (str_len <= 8) {
          uint64_t match = 0;
          for (size_type i = 0; i < str_len; ++i) {
            uint64_t xored = block ^ tapes[i];
            match |= ((xored - lsb64) & ~xored & msb64);
          }
          if (match != 0) {
            unsigned shift = 63 - count_leading_zeros(match);
            return (ptr - data_) + (shift >> 3);
          }
        } else {
          uint64_t lookup[4] = {0};
          for (size_type i = 0; i < str_len; ++i) {
            uint8_t c = static_cast<uint8_t>(str[i]);
            lookup[c >> 6] |= (1ULL << (c & 63));
          }
          for (size_type i = tape_size; i > 0; --i) {
            uint8_t c = static_cast<uint8_t>(ptr[i - 1]);
            if (lookup[c >> 6] & (1ULL << (c & 63))) {
              return (ptr - data_) + i - 1;
            }
          }
        }
        pos -= tape_size;
      }
    }

    for (size_type i = pos + 1; i > 0; --i) {
      for (size_type j = 0; j < str_len; ++j) {
        if (data_[i - 1] == str[j])
          return i - 1;
      }
    }
    return npos;
  }

  constexpr size_type find_last_not_of_impl(const CharT *str, size_type str_len,
                                            size_type pos) const noexcept {
    if (length_ == 0) {
      return npos;
    }

    if (str_len == 0) {
      return pos < length_ ? pos : length_ - 1;
    }

    pos = pos < length_ ? pos : length_ - 1;

    if (!is_constant_eval_() && sizeof(CharT) == 1) {
      tape_type tapes[tape_size]{};
      size_type tape_count = str_len < tape_size ? str_len : tape_size;
      for (size_type i = 0; i < tape_count; ++i)
        tapes[i] = make_tape(str[i]);

      while (pos >= tape_size - 1) {
        const CharT *ptr = data_ + pos - (tape_size - 1);
        uint64_t block{};
        std::memcpy(&block, ptr, tape_size);

        if (str_len <= 8) {
          uint64_t match = 0;
          for (size_type i = 0; i < str_len; ++i) {
            uint64_t xored = block ^ tapes[i];
            match |= ((xored - lsb64) & ~xored & msb64);
          }
          uint64_t not_match = ~match & msb64;
          if (not_match != 0) {
            unsigned shift = 63 - count_leading_zeros(not_match);
            return (ptr - data_) + (shift >> 3);
          }
        } else {
          uint64_t lookup[4] = {0};
          for (size_type i = 0; i < str_len; ++i) {
            uint8_t c = static_cast<uint8_t>(str[i]);
            lookup[c >> 6] |= (1ULL << (c & 63));
          }
          for (size_type i = tape_size; i > 0; --i) {
            uint8_t c = static_cast<uint8_t>(ptr[i - 1]);
            if (!(lookup[c >> 6] & (1ULL << (c & 63)))) {
              return (ptr - data_) + i - 1;
            }
          }
        }
        pos -= tape_size;
      }
    }

    for (size_type i = pos + 1; i > 0; --i) {
      bool found = false;
      for (size_type j = 0; j < str_len; ++j) {
        if (data_[i - 1] == str[j]) {
          found = true;
          break;
        }
      }
      if (!found)
        return i - 1;
    }
    return npos;
  }
};

#if (__cplusplus >= 201703L)
template <typename CharT>
basic_string_view(const CharT *, uint32_t) -> basic_string_view<CharT>;

template <typename CharT>
basic_string_view(const CharT *, const CharT *) -> basic_string_view<CharT>;
#endif

using string_view = basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;

#if defined(__cpp_char8_t) || (__cplusplus >= 202002L)
using u8string_view = basic_string_view<char8_t>;
#endif

using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;

} // namespace zuu

#endif // ZUU_STRING_VIEW_HPP