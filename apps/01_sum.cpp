#include <iostream>

/**
 * calculates and prints the sum of all the
 * natural numbers divisible by either 3 or 5,
 * up to a given limit entered by the user.
 * @param  argc [description]
 * @param  argv [description]
 * @return      [description]
 */
int main() {
    int limit = 3;
    std::cout << "Limit: ";
    std::cin >> limit;

    if (limit < 0) return -1;

    int sum = 0;
    for (int num = 0; num <= limit; num++) {
        if ((num % 3 == 0) || (num % 5 == 0)) sum += num;
    }

    std::cout << "Sum: " << sum << std::endl;
}