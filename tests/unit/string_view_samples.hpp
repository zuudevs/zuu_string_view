#ifndef STRV_SAMPLES_HPP
#define STRV_SAMPLES_HPP

#include <cstddef>
#include <gtest/gtest.h>
#include <zuu/string_view.hpp>

static constexpr size_t str_len = 12;
static constexpr const char str[str_len] = "Hello World";
static constexpr zuu::string_view str_zuu = str;
static std::string str_std = str;

#endif // STRV_SAMPLES_HPP