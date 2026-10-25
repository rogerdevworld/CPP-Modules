#include "MutantStack.hpp"
#include <iostream>
#include <list>

int main() {
    std::cout << "=== Test con MutantStack ===" << std::endl;
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << "Top: " << mstack.top() << std::endl; // Muestra 17

    mstack.pop();

    std::cout << "Size después de pop: " << mstack.size() << std::endl; // Muestra 1

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;

    std::cout << "Elementos en la pila:" << std::endl;
    while (it != ite) {
        std::cout << *it << std::endl;
        ++it;
    }

    std::stack<int> s(mstack); // Comprobación de copia al stack original

    return 0;
}