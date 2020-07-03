#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>
#include "ch1/ch1.hpp"

/**
 * Calculate and print the greatest common divisor of two integers
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main(int argc, char const *argv[]) {
    std::vector<int> numbers{};

    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            std::istringstream iss(argv[i]);
            int val;

            if (iss >> val) {
                // Conversion successful
                numbers.push_back(val);
            }
        }

    }

    int result = std::accumulate(numbers.begin(), numbers.end(), 1, lcm);

    std::cout << "Lowest common multiple: " << result << std::endl;
}
