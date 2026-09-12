#include "strv_samples.hpp"

TEST(find_apis, find) {
	strv str_view = str;

	// find first of 'l' character in "Hello World"
	auto first_l_ch = str_view.find('l');
	
	// find second of 'l' character in "Hello World"
	auto second_l_ch = str_view.find('l', first_l_ch + 1);

	// find last of 'l' character in "Hello World"
	auto last_l_ch = str_view.find('l', second_l_ch + 1);

	// find first of "ll" text in "Hello World"
	auto first_ll_tx_raw = str_view.find("ll");
	auto first_ll_tx_raw_with_hint = str_view.find("ll", 0, 2);
	auto first_ll_tx_zuu = str_view.find(strv{"ll"});
	auto first_ll_tx_std = str_view.find(std::string{"ll"});

	EXPECT_EQ(first_l_ch, 2);
	EXPECT_EQ(second_l_ch, 3);
	EXPECT_EQ(last_l_ch, 9);

	EXPECT_EQ(first_ll_tx_raw, 2);
	EXPECT_EQ(first_ll_tx_raw_with_hint, 2);
	EXPECT_EQ(first_ll_tx_zuu, 2);
	EXPECT_EQ(first_ll_tx_std, 2);
}

TEST(find_apis, rfind) {
	strv str_view = str;

	// find last of 'l' character in "Hello World"
	auto last_l_ch = str_view.rfind('l');
	
	// find second of 'l' character in "Hello World"
	auto second_l_ch = str_view.rfind('l', last_l_ch - 1);

	// find first of 'l' character in "Hello World"
	auto first_l_ch = str_view.rfind('l', second_l_ch - 1);

	// find last of "ll" text in "Hello World"
	auto last_ll_tx_raw = str_view.rfind("ll");
	auto last_ll_tx_raw_with_hint = str_view.rfind("ll", 11, 2);
	auto last_ll_tx_zuu = str_view.rfind(strv{"ll"});
	auto last_ll_tx_std = str_view.rfind(std::string{"ll"});

	EXPECT_EQ(last_l_ch, 9);
	EXPECT_EQ(second_l_ch, 3);
	EXPECT_EQ(first_l_ch, 2);

	EXPECT_EQ(last_ll_tx_raw, 2);
	EXPECT_EQ(last_ll_tx_raw_with_hint, 2);
	EXPECT_EQ(last_ll_tx_zuu, 2);
	EXPECT_EQ(last_ll_tx_std, 2);
}

TEST(find_apis, find_first_of) {
	strv str_view = str;

	// find_first_of first of 'l' character in "Hello World"
	auto first_l_ch = str_view.find_first_of('l');
	
	// find_first_of second of 'l' character in "Hello World"
	auto second_l_ch = str_view.find_first_of('l', first_l_ch + 1);

	// find_first_of last of 'l' character in "Hello World"
	auto last_l_ch = str_view.find_first_of('l', second_l_ch + 1);

	// find_first_of first of "ll" text in "Hello World"
	auto first_ll_tx_raw = str_view.find_first_of("ll");
	auto first_ll_tx_raw_with_hint = str_view.find_first_of("ll", 0, 2);
	auto first_ll_tx_zuu = str_view.find_first_of(strv{"ll"});
	auto first_ll_tx_std = str_view.find_first_of(std::string{"ll"});

	EXPECT_EQ(first_l_ch, 2);
	EXPECT_EQ(second_l_ch, 3);
	EXPECT_EQ(last_l_ch, 9);

	EXPECT_EQ(first_ll_tx_raw, 2);
	EXPECT_EQ(first_ll_tx_raw_with_hint, 2);
	EXPECT_EQ(first_ll_tx_zuu, 2);
	EXPECT_EQ(first_ll_tx_std, 2);
}

TEST(find_apis, find_last_of) {
	strv str_view = str;

	// find last of 'l' character in "Hello World"
	auto last_l_ch = str_view.find_last_of('l');
	
	// find second of 'l' character in "Hello World"
	auto second_l_ch = str_view.find_last_of('l', last_l_ch - 1);

	// find first of 'l' character in "Hello World"
	auto first_l_ch = str_view.find_last_of('l', second_l_ch - 1);

	// find last of "ll" text in "Hello World"
	auto last_ll_tx_raw = str_view.find_last_of("ll");
	auto last_ll_tx_raw_with_hint = str_view.find_last_of("ll", 11, 2);
	auto last_ll_tx_zuu = str_view.find_last_of(strv{"ll"});
	auto last_ll_tx_std = str_view.find_last_of(std::string{"ll"});

	EXPECT_EQ(last_l_ch, 9);
	EXPECT_EQ(second_l_ch, 3);
	EXPECT_EQ(first_l_ch, 2);

	EXPECT_EQ(last_ll_tx_raw, 9);
	EXPECT_EQ(last_ll_tx_raw_with_hint, 9);
	EXPECT_EQ(last_ll_tx_zuu, 9);
	EXPECT_EQ(last_ll_tx_std, 9);
}