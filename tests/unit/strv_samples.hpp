#ifndef STRV_SAMPLES_HPP
#define STRV_SAMPLES_HPP

#include <cstddef>
#include <gtest/gtest.h>
#include <strv.hpp>

static constexpr size_t str_len = 12;
static constexpr const char str[str_len] = "Hello World";
static constexpr zuu::strv str_zuu = str;
static std::string str_std = str;

#endif // STRV_SAMPLES_HPP