#include <cstdlib>
#include <iostream>

void error(std::string from, std::string message) {
    std::cerr << "ERROR from " << from << ":\n\t"
              << message << std::endl;

    std::exit(EXIT_FAILURE);
}