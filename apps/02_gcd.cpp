#include <iostream>
#include "ch1/ch1.hpp"

/**
 * Calculate and print the greatest common divisor of two integers
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main() {
    int first = 0;
    std::cout << "First: ";
    std::cin >> first;

    int second = 0;
    std::cout << "Second: ";
    std::cin >> second;

    std::cout << "Divisor: " << gcd(first, second) << std::endl;
}