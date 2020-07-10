#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include "ch1/ch1.hpp"

int main() {
	// int first =0;
 //    std::cout << "First: ";
 //    std::cin >> first;

 //    int second = 0;
 //    std::cout << "Second: ";
 //    std::cin >> second;

 //    std::cout << first << second << std::endl;

	IPV4Address a;
    std::cout << "First: ";
    std::cin >> a;

    IPV4Address b;
    std::cout << "Second: ";
    std::cin >> b;

    for (IPV4Address i = a; i <= b; i++) {
    	std::cout << i << '\n';
    }

    // std::cout << "Lowest common multiple: " << result << std::endl;
    //
}
