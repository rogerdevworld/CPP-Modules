#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &obj) : _vectorStack(obj._vectorStack), _dequeStack(obj._dequeStack) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &obj)
{
    if (this != &obj)
    {
        _vectorStack = obj._vectorStack;
        _dequeStack = obj._dequeStack;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

bool PmergeMe::parseArg(int argc, char **argv)
{
    if (argc < 2)
        return false;
    for (int i = 1; i < argc; i++)
    {
        std::stringstream ss(argv[i]);
        long number;
        char residuo;
        if (!(ss >> number) || (ss >> residuo) || number > INT_MAX || number <= 0)
            return false;
        
        _vectorStack.push_back(static_cast<int>(number));
        _dequeStack.push_back(static_cast<int>(number));
    }
    return true;
}

bool PmergeMe::compareFirstElement(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.first < b.first;
}

std::vector<size_t> PmergeMe::generateJacobsthalOrder(size_t n)
{
    std::vector<size_t> order;
    if (n <= 1)
        return order;
    
    std::vector<size_t> jacob;
    jacob.push_back(3);
    while (jacob.back() < n)
    {
        size_t penultimate;
        if (jacob.size() >= 2)
            penultimate = jacob[jacob.size() - 2];
        else
            penultimate = 1;
        size_t next = jacob.back() + 2 * penultimate;
        jacob.push_back(next);
    }
    
    size_t last = 1;
    for (size_t i = 0; i < jacob.size(); i++)
    {
        size_t current = jacob[i];
        size_t limit;
        if (current <= n)
            limit = current;
        else
            limit = n;
            
        for (size_t k = limit; k > last; --k)
            order.push_back(k);
        last = limit;
        if (last >= n)
            break;
    }
    return order;
}

void PmergeMe::sortVector(std::vector<int> &v)
{
    if (v.size() <= 1)
        return;
        
    int leftover = -1;
    if (v.size() % 2 != 0)
        leftover = v.back();
        
    std::vector<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < v.size(); i += 2)
    {
        if (v[i] >= v[i+1])
            pairs.push_back(std::make_pair(v[i], v[i+1]));
        else
            pairs.push_back(std::make_pair(v[i+1], v[i]));
    }
    
    std::sort(pairs.begin(), pairs.end(), compareFirstElement);
    
    std::vector<int> mainChain;
    std::vector<int> pendingElements;
    mainChain.reserve(v.size());
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].first);
        pendingElements.push_back(pairs[i].second);
    }
    
    if (!pendingElements.empty())
        mainChain.insert(mainChain.begin(), pendingElements[0]);

    std::vector<size_t> order = generateJacobsthalOrder(pendingElements.size());
    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i] - 1;
        int val = pendingElements[index];
        int pairMatch = pairs[index].first;
        
        std::vector<int>::iterator superiorLimit = std::find(mainChain.begin(), mainChain.end(), pairMatch);
        std::vector<int>::iterator insertPos = std::lower_bound(mainChain.begin(), superiorLimit, val);
        mainChain.insert(insertPos, val);
    }
    
    if (leftover != -1)
    {
        std::vector<int>::iterator insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
        mainChain.insert(insertPos, leftover);
    }
    v = mainChain;
}

void PmergeMe::sortDeque(std::deque<int> &d)
{
    if (d.size() <= 1)
        return;
        
    int leftover = -1;
    if (d.size() % 2 != 0)
        leftover = d.back();
        
    std::deque<std::pair<int, int> > pairs;
    for (size_t i = 0; i + 1 < d.size(); i += 2)
    {
        if (d[i] >= d[i+1])
            pairs.push_back(std::make_pair(d[i], d[i+1]));
        else
            pairs.push_back(std::make_pair(d[i+1], d[i]));
    }
    
    std::sort(pairs.begin(), pairs.end(), compareFirstElement);
    
    std::deque<int> mainChain;
    std::deque<int> pendingElements;
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        mainChain.push_back(pairs[i].first);
        pendingElements.push_back(pairs[i].second);
    }
    
    if (!pendingElements.empty())
        mainChain.insert(mainChain.begin(), pendingElements[0]);
        
    std::vector<size_t> order = generateJacobsthalOrder(pendingElements.size());
    for (size_t i = 0; i < order.size(); i++)
    {
        size_t index = order[i] - 1;
        int val = pendingElements[index];
        int pairMatch = pairs[index].first;
        
        std::deque<int>::iterator superiorLimit = std::find(mainChain.begin(), mainChain.end(), pairMatch);
        std::deque<int>::iterator insertPos = std::lower_bound(mainChain.begin(), superiorLimit, val);
        mainChain.insert(insertPos, val);
    }
    
    if (leftover != -1)
    {
        std::deque<int>::iterator insertPos = std::lower_bound(mainChain.begin(), mainChain.end(), leftover);
        mainChain.insert(insertPos, leftover);
    }
    d = mainChain;
}

void PmergeMe::run()
{
    std::cout << "Before: ";
    for (size_t i = 0; i < _dequeStack.size(); i++)
        std::cout << _dequeStack[i] << (i + 1 < _dequeStack.size() ? " " : "");
    std::cout << std::endl;

    clock_t startVect = clock();
    sortVector(_vectorStack);
    clock_t endVect = clock();
    double timeVec = static_cast<double>(endVect - startVect) / CLOCKS_PER_SEC * 1000000.0;

    clock_t startDeq = clock();
    sortDeque(_dequeStack);
    clock_t endDeq = clock();
    double timeDeq = static_cast<double>(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "After : ";
    for (size_t i = 0; i < _dequeStack.size(); i++)
        std::cout << _dequeStack[i] << (i + 1 < _dequeStack.size() ? " " : "");
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << _vectorStack.size()
              << " elements with std::vector : " << timeVec << " us" << std::endl;
    std::cout << "Time to process a range of " << _dequeStack.size()
              << " elements with std::deque  : " << timeDeq << " us" << std::endl;
}