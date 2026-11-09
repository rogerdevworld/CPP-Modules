#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <algorithm>
# include <iomanip>
# include <sstream>
# include <ctime>
# include <climits>
# include <vector>
# include <deque>

class PmergeMe
{
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &obj);
        PmergeMe &operator=(const PmergeMe &obj);
        ~PmergeMe();

        bool parseArg(int argc, char **argv);
        static bool compareFirstElement(const std::pair<int, int>& a, const std::pair<int, int>& b);
        std::vector<size_t> generateJacobsthalOrder(size_t n);
        void sortVector(std::vector<int> &v);
        void sortDeque(std::deque<int> &d);
        void run();

    private:
        std::vector<int> _vectorStack;
        std::deque<int> _dequeStack;
};

#endif