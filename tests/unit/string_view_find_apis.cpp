#include "string_view_samples.hpp"

TEST(find_apis, find) {
  zuu::string_view str_view = str;

  // find first of 'l' character in "Hello World"
  auto first_l_ch = str_view.find('l');

  // find second of 'l' character in "Hello World"
  auto second_l_ch = str_view.find('l', first_l_ch + 1);

  // find last of 'l' character in "Hello World"
  auto last_l_ch = str_view.find('l', second_l_ch + 1);

  // find first of "ll" text in "Hello World"
  auto first_ll_tx_raw = str_view.find("ll");
  auto first_ll_tx_raw_with_hint = str_view.find("ll", 0, 2);
  auto first_ll_tx_zuu = str_view.find(zuu::string_view{"ll"});
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
  zuu::string_view str_view = str;

  // find last occurrence of 'l' character in "Hello World" (backward)
  auto last_l_ch = str_view.rfind('l');

  // find second occurrence of 'l' character backwards from hint
  auto second_l_ch = str_view.rfind('l', last_l_ch - 1);

  // find earlier occurrence of 'l' character backwards from hint
  auto first_l_ch = str_view.rfind('l', second_l_ch - 1);

  // find last occurrence of "ll" text in "Hello World" (backward)
  auto last_ll_tx_raw = str_view.rfind("ll");
  auto last_ll_tx_raw_with_hint = str_view.rfind("ll", 11, 2);
  auto last_ll_tx_zuu = str_view.rfind(zuu::string_view{"ll"});
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
  zuu::string_view str_view = str;

  // find first occurrence of any character 'l' in "Hello World"
  auto first_l_ch = str_view.find_first_of('l');

  // find next occurrence of any character 'l' in "Hello World"
  auto second_l_ch = str_view.find_first_of('l', first_l_ch + 1);

  // find last occurrence of any character 'l' in "Hello World" via
  // find_first_of
  auto last_l_ch = str_view.find_first_of('l', second_l_ch + 1);

  // find first occurrence of any character from "ll" text in "Hello World"
  auto first_ll_tx_raw = str_view.find_first_of("ll");
  auto first_ll_tx_raw_with_hint = str_view.find_first_of("ll", 0, 2);
  auto first_ll_tx_zuu = str_view.find_first_of(zuu::string_view{"ll"});
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
  zuu::string_view str_view = str;

  // find last occurrence of any character 'l' searching backwards in "Hello
  // World"
  auto last_l_ch = str_view.find_last_of('l');

  // find previous occurrence of any character 'l' searching backwards
  auto second_l_ch = str_view.find_last_of('l', last_l_ch - 1);

  // find earlier occurrence of any character 'l' searching backwards
  auto first_l_ch = str_view.find_last_of('l', second_l_ch - 1);

  // find last occurrence of any character from "ll" searching backwards
  auto last_ll_tx_raw = str_view.find_last_of("ll");
  auto last_ll_tx_raw_with_hint = str_view.find_last_of("ll", 11, 2);
  auto last_ll_tx_zuu = str_view.find_last_of(zuu::string_view{"ll"});
  auto last_ll_tx_std = str_view.find_last_of(std::string{"ll"});

  EXPECT_EQ(last_l_ch, 9);
  EXPECT_EQ(second_l_ch, 3);
  EXPECT_EQ(first_l_ch, 2);

  EXPECT_EQ(last_ll_tx_raw, 9);
  EXPECT_EQ(last_ll_tx_raw_with_hint, 9);
  EXPECT_EQ(last_ll_tx_zuu, 9);
  EXPECT_EQ(last_ll_tx_std, 9);
}

TEST(find_apis, find_first_not_of) {
  zuu::string_view str_view = str;

  // find first character that is NOT 'l' in "Hello World"
  auto first_not_l_ch = str_view.find_first_not_of('l');

  // find next character that is NOT 'l' starting from hint
  auto second_not_l_ch = str_view.find_first_not_of('l', first_not_l_ch + 1);

  // find later character that is NOT 'l' starting from hint
  auto last_not_l_ch = str_view.find_first_not_of('l', second_not_l_ch + 1);

  // find first character that is NOT part of "ll" in "Hello World"
  auto first_not_ll_tx_raw = str_view.find_first_not_of("ll");
  auto first_not_ll_tx_raw_with_hint = str_view.find_first_not_of("ll", 0, 2);
  auto first_not_ll_tx_zuu = str_view.find_first_not_of(zuu::string_view{"ll"});
  auto first_not_ll_tx_std = str_view.find_first_not_of(std::string{"ll"});

  EXPECT_EQ(first_not_l_ch, 0);
  EXPECT_EQ(second_not_l_ch, 1);
  EXPECT_EQ(last_not_l_ch, 4);

  EXPECT_EQ(first_not_ll_tx_raw, 0);
  EXPECT_EQ(first_not_ll_tx_raw_with_hint, 0);
  EXPECT_EQ(first_not_ll_tx_zuu, 0);
  EXPECT_EQ(first_not_ll_tx_std, 0);
}

TEST(find_apis, find_last_not_of) {
  zuu::string_view str_view = str;

  // find last character that is NOT 'l' searching backwards in "Hello World"
  auto last_l_ch = str_view.find_last_not_of('l');

  // find previous character that is NOT 'l' searching backwards
  auto second_l_ch = str_view.find_last_not_of('l', last_l_ch - 1);

  // find earlier character that is NOT 'l' searching backwards
  auto first_l_ch = str_view.find_last_not_of('l', second_l_ch - 1);

  // find last character that is NOT part of "ll" searching backwards
  auto last_ll_tx_raw = str_view.find_last_not_of("ll");
  auto last_ll_tx_raw_with_hint = str_view.find_last_not_of("ll", 11, 2);
  auto last_ll_tx_zuu = str_view.find_last_not_of(zuu::string_view{"ll"});
  auto last_ll_tx_std = str_view.find_last_not_of(std::string{"ll"});

  EXPECT_EQ(last_l_ch, 10);
  EXPECT_EQ(second_l_ch, 8);
  EXPECT_EQ(first_l_ch, 7);

  EXPECT_EQ(last_ll_tx_raw, 10);
  EXPECT_EQ(last_ll_tx_raw_with_hint, 10);
  EXPECT_EQ(last_ll_tx_zuu, 10);
  EXPECT_EQ(last_ll_tx_std, 10);
}