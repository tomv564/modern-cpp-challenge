#include <filesystem>
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

	Logger logger;
	std::cout << "logging to " << std::filesystem::temp_directory_path() << "\n";
	logger << "taking input" << "\n";
	IPV4Address a;
    std::cout << "First: ";
    std::cin >> a;

    IPV4Address b;
    std::cout << "Second: ";
    std::cin >> b;

    logger << "writing range" << "\n";

    for (IPV4Address i = a; i <= b; i++) {
    	std::cout << i << '\n';
    }

    logger << "done" << "\n";
    logger.archive(std::filesystem::current_path() / "log.txt");
    // std::cout << "Lowest common multiple: " << result << std::endl;
    //
}
