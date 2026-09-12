#include "string_view_samples.hpp"
#include <utility>

TEST(ctor_test, default_ctor) {
  constexpr zuu::string_view view{};

  EXPECT_EQ(view.data(), nullptr);
  EXPECT_EQ(view.size(), 0u);
  EXPECT_TRUE(view.empty());
}

TEST(ctor_test, raw_pointer) {
  zuu::string_view str1(str);
  std::string str2(str);

  EXPECT_STREQ(str1.data(), str);
  EXPECT_STREQ(str2.data(), str);
  EXPECT_STREQ(str1.data(), str2.data());
  EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, raw_pointer_with_len) {
  zuu::string_view str1(str, str_len);
  std::string str2(str, str_len);

  EXPECT_STREQ(str1.data(), str);
  EXPECT_STREQ(str2.data(), str);
  EXPECT_STREQ(str1.data(), str2.data());
  EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, paired_raw_pointer) {
  zuu::string_view str1(str, str + str_len);
  std::string str2(str, str + str_len);

  EXPECT_STREQ(str1.data(), str);
  EXPECT_STREQ(str2.data(), str);
  EXPECT_STREQ(str1.data(), str2.data());
  EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, std_string) {
  zuu::string_view str1(str_std);
  std::string str2(str_std);

  EXPECT_STREQ(str1.data(), str);
  EXPECT_STREQ(str2.data(), str);
  EXPECT_STREQ(str1.data(), str2.data());
  EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, copy_ctor) {
  zuu::string_view str1(str_zuu);
  std::string str2(str_zuu);

  EXPECT_STREQ(str1.data(), str);
  EXPECT_STREQ(str2.data(), str);
  EXPECT_STREQ(str1.data(), str2.data());
  EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, move_ctor) {
  auto str_zuu_target = str_zuu;
  auto str_std_target = str_std;

  zuu::string_view str1(std::move(str_zuu_target));
  std::string str2(std::move(str_zuu_target));

  zuu::string_view str3(std::move(str_std_target));
  std::string str4(std::move(str_std_target));

  EXPECT_STREQ(str1.data(), str);
  EXPECT_STREQ(str2.data(), str);
  EXPECT_STREQ(str1.data(), str2.data());
  EXPECT_EQ(str1.size(), str2.length());

  EXPECT_EQ(str1.size(), str_zuu_target.size());
  EXPECT_EQ(str2.length(), str_zuu_target.size());

  EXPECT_NE(str3.size(), str_std_target.length());
  EXPECT_NE(str4.length(), str_std_target.length());
}