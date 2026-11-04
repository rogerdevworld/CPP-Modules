#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <algorithm>
# include <string>
# include <sstream>
# include <fstream>
# include <stdexcept>
# include <iostream>
# include <map>
# include <iomanip>


class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &obj);
        BitcoinExchange& operator=(const BitcoinExchange &obj);
        ~BitcoinExchange();

        void readCsv(const std::string &filename);
        void readInput(const std::string &filename) const;
    private:
        std::map<std::string, double> _db;
        bool validDate(const std::string &date) const;
        bool validValue(const std::string &valueStr, double &value) const;

        std::string trim(const std::string &s) const;
        std::map<std::string, double>::const_iterator findRate(const std::string &date) const;
        
        
};

#endif