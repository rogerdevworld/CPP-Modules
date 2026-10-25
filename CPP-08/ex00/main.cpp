#include "easyfind.hpp"
#include <vector>
#include <list>
#include <iostream>

int main() {
    std::cout << "=== Test 1: std::vector ===" << std::endl;
    try {
        std::vector<int> vec;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        vec.push_back(40);

        std::vector<int>::iterator it = easyfind(vec, 30);
        std::cout << "Encontrado en vector: " << *it << std::endl;

        std::cout << "Buscando elemento inexistente (99)..." << std::endl;
        easyfind(vec, 99);
    } 
    catch (const std::exception& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
    }

    std::cout << "\n=== Test 2: std::list ===" << std::endl;
    try {
        std::list<int> lst;
        lst.push_back(100);
        lst.push_back(200);
        lst.push_back(300);

        std::list<int>::iterator it = easyfind(lst, 200);
        std::cout << "Encontrado en list: " << *it << std::endl;

        std::cout << "Buscando elemento inexistente (500)..." << std::endl;
        easyfind(lst, 500);
    } 
    catch (const std::exception& e) {
        std::cerr << "Excepción atrapada: " << e.what() << std::endl;
    }

    return 0;
}