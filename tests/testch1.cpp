#include "ch1/ch1.hpp"
#include "gtest/gtest.h"

TEST(Ch1, GCD) {
	EXPECT_EQ(gcd(0, 0), 0);
}

TEST(Ch1, LCM) {
	EXPECT_EQ(lcm(3, 4), 12);
}

TEST(Ch1, Roman) {
	ASSERT_STREQ(to_roman(1994).c_str(), "MCMXCIV");
}

TEST(Ch1, ISBN10) {
	EXPECT_FALSE(is_valid_isbn10("123"));
	EXPECT_FALSE(is_valid_isbn10("0000000100")); //

	// note: char "O"
	EXPECT_FALSE(is_valid_isbn10("O306406152")); // 0-306-40615-2

	EXPECT_TRUE(is_valid_isbn10("0306406152")); // 0-306-40615-2
}