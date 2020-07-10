#include <iterator>
#include <list>
#include "ch1/ch1.hpp"
#include "gtest/gtest.h"

TEST(Ch1, GCD) { EXPECT_EQ(gcd(0, 0), 0); }

TEST(Ch1, LCM) { EXPECT_EQ(lcm(3, 4), 12); }

TEST(Ch1, Roman) { ASSERT_STREQ(to_roman(1994).c_str(), "MCMXCIV"); }

TEST(Ch1, ISBN10) {
    EXPECT_FALSE(is_valid_isbn10("123"));
    EXPECT_FALSE(is_valid_isbn10("0000000100"));  //

    // note: char "O"
    EXPECT_FALSE(is_valid_isbn10("O306406152"));  // 0-306-40615-2

    EXPECT_TRUE(is_valid_isbn10("0306406152"));  // 0-306-40615-2
}

TEST(LANGFEAT, IPV4ADDR) {
    IPV4Address a(192, 168, 0, 1);
    IPV4Address b(192, 168, 1, 0);
    EXPECT_TRUE(a < b);
    // std::cout << address << std::endl;

    // IPV4Address ip;
    // std::cout << ip << std::endl;
    // std::cin >> ip;
    // if (!std::cin.fail()) std::cout << ip << std::endl;

}

TEST(LANGFEAT, 2DARRAY) {
    array2d<int, 2, 3> a{1, 2, 3, 4, 5, 6};

    // element access, should throw out_of_range exception
    EXPECT_EQ(a.at(1, 2), 6);

    // raw
    int* first = a.data();
    EXPECT_EQ(1, *first);

    // capacity

    // iterators
    // std::copy(std::begin(a), std::end(a), std::ostream_iterator<int>(std::cout, " "));
    for (auto&& num : a) {
        std::cout << num << " ";
    }

    // filling
    a.fill(3);

    // swapping

    // move

}

TEST(LANGFEAT, MINIMUM)
{
    ASSERT_EQ(3, minimum(3, 6, 8, 9));
}

TEST(LANGFEAT, ANYALLNONE)
{
    std::vector<int> v{ 1, 2, 3, 4, 5, 6 };
    assert(contains_any(v, 0, 3, 30));

    std::array<int, 6> a{ { 1, 2, 3, 4, 5, 6 } };
    assert(contains_all(a, 1, 3, 5, 6));

    std::list<int> l{ 1, 2, 3, 4, 5, 6 };
    assert(!contains_none(l, 0, 6));
}

TEST(STRINGS, CAPITALIZE)
{
    ASSERT_EQ(capitalize("the c++ challenger"), "The C++ Challenger");
}

TEST(STRINGS, LICENSEPLATE)
{
    ASSERT_FALSE(validate_license_plate("324234234"));
    ASSERT_TRUE(validate_license_plate("ABC-DE 678"));
}