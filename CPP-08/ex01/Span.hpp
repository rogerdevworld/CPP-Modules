#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <exception>
#include <algorithm>
#include <iterator>
#include <stdexcept>

class Span {
private:
    unsigned int _maxSize;
    std::vector<int> _numbers;

    Span(); // Constructor por defecto privado

public:
    Span(unsigned int N);
    Span(const Span& other);
    Span& operator=(const Span& other);
    ~Span();

    void addNumber(int number);
    
    // Función plantilla para rangos de iteradores (debe ir en el header)
    template <typename InputIterator>
    void addRange(InputIterator begin, InputIterator end) {
        if (_numbers.size() + std::distance(begin, end) > _maxSize)
            throw std::out_of_range("Adding range exceeds capacity");
        _numbers.insert(_numbers.end(), begin, end);
    }

    int shortestSpan() const;
    int longestSpan() const;
};

#endif