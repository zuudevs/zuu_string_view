#include <cstdint>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>
#include <zuu/string_view.hpp>

namespace {

void expect_same(zuu::string_view::size_type actual,
                 std::string_view::size_type expected) {
  if (expected == std::string_view::npos) {
    EXPECT_EQ(actual, zuu::string_view::npos);
    return;
  }

  ASSERT_LE(expected,
            static_cast<std::string_view::size_type>(
                std::numeric_limits<zuu::string_view::size_type>::max()));
  EXPECT_EQ(actual, static_cast<zuu::string_view::size_type>(expected));
}

} // namespace

TEST(string_view_differential, search_apis_match_std_string_view) {
  const std::vector<std::string> haystacks = {
      "",
      "a",
      "aaaa",
      "abcdef",
      "abcabcabc",
      "Hello World",
      std::string("a\0ba", 4),
  };
  const std::vector<std::string> needles = {
      "",
      "a",
      "b",
      "x",
      "aa",
      "ab",
      "abc",
      "World",
      std::string("\0", 1),
      std::string("a\0", 2),
  };
  const std::vector<char> characters = {'a', 'b', 'x', '\0'};

  for (const std::string& haystack : haystacks) {
    const zuu::string_view actual(haystack.data(),
                                  static_cast<zuu::string_view::size_type>(
                                      haystack.size()));
    const std::string_view expected(haystack.data(), haystack.size());

    std::vector<std::size_t> positions = {
        0,
        1,
        haystack.size() / 2,
        haystack.size(),
        haystack.size() + 1,
        std::string_view::npos,
    };

    for (std::size_t pos : positions) {
      const zuu::string_view::size_type actual_pos =
          static_cast<zuu::string_view::size_type>(pos);

      for (char ch : characters) {
        expect_same(actual.find(ch, actual_pos), expected.find(ch, pos));
        expect_same(actual.rfind(ch, actual_pos), expected.rfind(ch, pos));
        expect_same(actual.find_first_of(ch, actual_pos),
                    expected.find_first_of(ch, pos));
        expect_same(actual.find_last_of(ch, actual_pos),
                    expected.find_last_of(ch, pos));
        expect_same(actual.find_first_not_of(ch, actual_pos),
                    expected.find_first_not_of(ch, pos));
        expect_same(actual.find_last_not_of(ch, actual_pos),
                    expected.find_last_not_of(ch, pos));
      }

      for (const std::string& needle : needles) {
        const std::string_view needle_view(needle.data(), needle.size());

        expect_same(actual.find(needle_view, actual_pos),
                    expected.find(needle_view, pos));
        expect_same(actual.rfind(needle_view, actual_pos),
                    expected.rfind(needle_view, pos));
        expect_same(actual.find_first_of(needle_view, actual_pos),
                    expected.find_first_of(needle_view, pos));
        expect_same(actual.find_last_of(needle_view, actual_pos),
                    expected.find_last_of(needle_view, pos));
        expect_same(actual.find_first_not_of(needle_view, actual_pos),
                    expected.find_first_not_of(needle_view, pos));
        expect_same(actual.find_last_not_of(needle_view, actual_pos),
                    expected.find_last_not_of(needle_view, pos));
      }
    }
  }
}
