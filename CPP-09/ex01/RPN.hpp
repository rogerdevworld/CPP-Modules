#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <sstream>
# include <exception>
# include <algorithm>
# include <numeric>
# include <stack>

class RPN
{
    public:
        RPN();
        RPN(const RPN &obj);
        RPN &operator=(const RPN &obj);
        ~RPN();

        int eval(const std::string &expression);
    private:
        std::stack<int> _stack;
};

#endif