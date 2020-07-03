#include <sys/cdefs.h>

#include <numeric>
#include <sstream>
#include <string>
#include <vector>

unsigned int gcd(unsigned int a, unsigned int b) {
    /* Euclid's algorithm
    gcd(a,0) = a
    gcd(a,b) = gcd(b, a mod b)
    */
    if (b == 0)
        return a;
    else {
        return gcd(b, a % b);
    }
}

unsigned int lcm(const int a, const int b) {
    int h = gcd(a, b);
    return h ? (a * (b / h)) : 0;
}

std::string to_roman(const int a) {
    int remaining = a;
    std::vector<std::pair<int, char const*>> mapping{
        {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"},
        {90, "XC"},  {50, "L"},   {40, "XL"}, {10, "X"},   {9, "IX"},
        {5, "V"},    {4, "IV"},   {1, "I"}};
    std::string output;

    for (const auto& pair : mapping) {
        while (remaining >= pair.first) {
            output += pair.second;
            remaining -= pair.first;
        }
    }
    return output;
}

bool is_valid_isbn10(std::string isbn) {
    /*
    sum of the ten digits, each multiplied by its (integer) weight, descending
    from 10 to 1, is a multiple of 11.
     */



    // TODO: rewrite using
    // string_view
    // count_if(... isdigit)
    // std::accumulate
    // ascii math (c - '10')

    // TODO: support hyphens
    if (isbn.size() != 10) {
        return false;
    }

    int check = 0;

    for (int i = 0; i < 10; i++) {
        try {
            int val = std::stoi(isbn.substr(i, 1));
            check += (10 - i) * val;
        } catch (std::exception& err) {
            return false;
        }
        // } else {
        // 	return false;
        // }
        // convert to int
    }

    return check % 11 == 0;
}