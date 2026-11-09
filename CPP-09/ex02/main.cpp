#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
    PmergeMe sorter;
    if (!sorter.parseArg(argc, argv))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    sorter.run();
    return 0;
}