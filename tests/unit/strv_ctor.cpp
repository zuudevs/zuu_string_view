#include <cstddef>
#include <gtest/gtest.h>
#include <utility>
#include <strv.hpp>

using namespace zuu;

constexpr size_t str_len = 12;
constexpr const char str[str_len] = "Hello World";
constexpr strv str_zuu = str;
std::string str_std = str;

TEST(ctor_test, raw_pointer) {
	strv str1(str);  
	std::string str2(str);

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, raw_pointer_with_len) {
	strv str1(str, str_len);
	std::string str2(str, str_len);

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, paired_raw_pointer) {
	strv str1(str, str + str_len);
	std::string str2(str, str + str_len);

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, std_string) {
	strv str1(str_std);
	std::string str2(str_std);

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, copy_ctor) {
	strv str1(str_zuu);
	std::string str2(str_zuu);

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(ctor_test, move_ctor) {
	auto str1_target = str_zuu;
	auto str2_target = str_std;

	strv str1(std::move(str1_target));
	std::string str2(std::move(str1_target));

	strv str3(std::move(str2_target));
	std::string str4(std::move(str2_target));

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());

	EXPECT_EQ(str1.size(), str1_target.size());
	EXPECT_EQ(str2.length(), str1_target.size());

	EXPECT_NE(str3.size(), str2_target.length());
	EXPECT_NE(str4.length(), str2_target.length());
}