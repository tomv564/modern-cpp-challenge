#include <sys/cdefs.h>
#include <ch1/ch1.hpp>

#include <cctype>
#include <numeric>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <regex>

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

bool is_valid_isbn10(std::string_view isbn) {
    /*
    sum of the ten digits, each multiplied by its (integer) weight, descending
    from 10 to 1, is a multiple of 11.
     */
    std::vector<int> digits{};
    for (char letter : isbn) {
        if (std::isdigit(letter)) {
            digits.emplace_back(letter - 'a');
        } else if (letter != '-') {
            return false;
        }
    }

    if (digits.size() != 10) return false;

    int pos = 10;
    int checksum = std::accumulate(digits.begin(), digits.end(), 0,
                                   [&pos](const int sum, const int digit) {
                                       return sum + (digit * pos--);
                                   });

    return checksum % 11 == 0;
}

std::string IPV4Address::to_string() const
{
    std::stringstream str;
    str << *this;
    return str.str();
}

unsigned long IPV4Address::to_ulong() const
{
    return static_cast<unsigned long>(m_value[0]) << 24 |
         static_cast<unsigned long>(m_value[1]) << 16 |
         static_cast<unsigned long>(m_value[2]) << 8 |
         static_cast<unsigned long>(m_value[3]);
}

std::istream& operator>>(std::istream& is, IPV4Address& addr)
{
    int a, b, c, d;
    char d1, d2, d3;
    is >> a >> d1 >> b >> d2 >> c >> d3 >> d;
    if (d1 == '.' && d2 == '.' && d3 == '.') {
        addr = IPV4Address(a, b, c, d);
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const IPV4Address& addr)
{
	os << static_cast<int>(addr.m_value[0]) << '.' << static_cast<int>(addr.m_value[1]) << '.' << static_cast<int>(addr.m_value[2]) << '.' << static_cast<int>(addr.m_value[3]);
	return os;
}

IPV4Address& operator++(IPV4Address& a)
{
    a = IPV4Address(a.to_ulong() + 1);
    return a;
}

IPV4Address operator++(IPV4Address& a, int)
{
    IPV4Address original(a);
    ++a;
    return original;
}

std::string capitalize(const std::string_view str)
{
    std::stringstream ss;
    bool isNewWord = true;
    for (auto& c : str)
    {
        if (isNewWord and std::isalpha(c)) {
            ss << static_cast<char>(std::toupper(c));
        } else {
            ss << c;
        }
        isNewWord = std::isspace(c) || std::ispunct(c);
    }

    return ss.str();
}

bool validate_license_plate(std::string_view str)
{
    // LLL-LL DDD
    std::regex re(R"([A-Z]{3}-[A-Z]{2} \d{3,4})");
    return std::regex_match(str.data(), re);
}
