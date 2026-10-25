#include "Span.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::cout << "=== Test del enunciado ===" << std::endl;
    try {
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest: " << sp.shortestSpan() << std::endl; // Muestra 2
        std::cout << "Longest:  " << sp.longestSpan() << std::endl;  // Muestra 14
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "\n=== Test de 10.000 elementos con addRange ===" << std::endl;
    try {
        Span bigSpan(10000);
        std::vector<int> bigVector;

        std::srand(std::time(NULL));
        for (int i = 0; i < 10000; ++i) {
            bigVector.push_back(std::rand());
        }

        bigSpan.addRange(bigVector.begin(), bigVector.end());

        std::cout << "Shortest (10k): " << bigSpan.shortestSpan() << std::endl;
        std::cout << "Longest (10k):  " << bigSpan.longestSpan() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}