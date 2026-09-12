#include "strv_samples.hpp"

TEST(substr_apis, substring) {
	zuu::strv str1 = str;

	// put "Hello" from "Hello World"
	auto sub1 = str1.substr(0, 5);

	// put "World" from "Hello World"
	auto sub2 = str1.substr(6, 5);

	EXPECT_EQ(str1.size(), 11);
	EXPECT_EQ(std::string(str1.data(), str1.size()), "Hello World");
	EXPECT_EQ(std::string(sub1.data(), sub1.size()), "Hello");
	EXPECT_EQ(std::string(sub2.data(), sub2.size()), "World");
}