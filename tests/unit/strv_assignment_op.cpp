#include "strv_samples.hpp"
#include <algorithm>

TEST(assignment_operator, raw_pointer) {
	strv str1;
	std::string str2;

	str1 = str;
	str2 = str;

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(assignment_operator, std_string) {
	strv str1;
	std::string str2;

	str1 = str_std;
	str2 = str_std;

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(assignment_operator, copy_assigment) {
	strv str1;
	std::string str2;

	str1 = str_zuu;
	str2 = str_zuu;

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());
}

TEST(assignment_operator, move_assigment) {
	auto str_zuu_target = str_zuu;
	auto str_std_target = str_std;
	
	strv str1, str3;
	std::string str2, str4;

	str1 = std::move(str_zuu_target);
	str2 = std::move(str_zuu_target);
	str3 = std::move(str_std_target);
	str4 = std::move(str_std_target);

	EXPECT_STREQ(str1.data(), str);
	EXPECT_STREQ(str2.data(), str);
	EXPECT_STREQ(str1.data(), str2.data());
	EXPECT_EQ(str1.size(), str2.length());

	EXPECT_EQ(str1.size(), str_zuu_target.size());
	EXPECT_EQ(str2.length(), str_zuu_target.size());

	EXPECT_NE(str3.size(), str_std_target.length());
	EXPECT_NE(str4.length(), str_std_target.length());
}