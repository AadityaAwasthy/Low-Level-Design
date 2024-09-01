#include "../Headers.h"


class ProductCodeGenerator {
    public:
        // Use size_t instead of int value as size_t is unsigned value so cannot be negative
        // size_t is implementation independent and guarantees to hold values that can be accomodated by 
        // the system.
        static string generate(size_t length) {
            // These strings are automcatically concatanated by the compliler
            const std::string characters = "abcdefghijklmnopqrstuvwxyz"
                                   "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                   "0123456789";

            random_device rd; // Random seed to generate different values every time
            mt19937 generator(rd()); // Mersenne twister generator for better random values
            uniform_int_distribution<> distribution(0, characters.size() - 1);

            string random_string(length, '\0');

            generate_n(random_string.begin(), length, [&](){
                    return characters[distribution(generator)];
                    });

            return random_string;
        }
};
