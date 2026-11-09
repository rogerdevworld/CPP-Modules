#include "BitcoinExchange.hpp"
BitcoinExchange::BitcoinExchange()
{   }

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj) : _db(obj._db)
{   }

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange &obj)
{
    if (this != &obj)
        _db = obj._db;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{   }

std::string BitcoinExchange::trim(const std::string &s) const
{
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

bool BitcoinExchange::validDate(const std::string &date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-') return false;

    for (size_t i = 0; i < date.size(); ++i)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(date[i]))
            return false;
    }

    int y = std::atoi(date.substr(0, 4).c_str());
    int m = std::atoi(date.substr(5, 2).c_str());
    int d = std::atoi(date.substr(8, 2).c_str());
    if (y < 2009 || m < 1 || m > 12) return false;

    int max_day[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
        max_day[2] = 29;

    return d >= 1 && d <= max_day[m];
}

bool BitcoinExchange::validValue(const std::string& valueStr, double& value) const 
{
    std::stringstream ss(valueStr);
    if (!(ss >> value))
        return false;
    char remaining;
    if (ss >> remaining)
        return false;
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

std::map<std::string, double>::const_iterator BitcoinExchange::findRate(const std::string &date) const
{
    std::map<std::string, double>::const_iterator it = _db.lower_bound(date);
    if (it == _db.end() || it->first != date)
    {
        if (it == _db.begin()) return _db.end();
        --it;
    }
    return it;
}

void BitcoinExchange::readCsv(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file)
        throw std::runtime_error("Error: could not open the CSV file.");
    std::string line;
    if (!std::getline(file, line))
        throw std::runtime_error("Error: database file is empty.");

    while (std::getline(file, line)) 
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string date, rateStr;
        if (!std::getline(ss, date, ',') || !std::getline(ss, rateStr)) continue;

        date = trim(date);
        rateStr = trim(rateStr);

        double rate = std::atof(rateStr.c_str());
        _db[date] = rate;
    }
}

void BitcoinExchange::readInput(const std::string &filename) const
{
    std::ifstream file(filename.c_str());
    if (!file)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) 
    {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string date, valueStr;

        if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = trim(date);
        valueStr = trim(valueStr);

        if (!validDate(date))
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        double value;
        if (!validValue(valueStr, value))
        {
            continue;
        }

        std::map<std::string, double>::const_iterator it = findRate(date);
        if (it == _db.end())
        {
            std::cerr << "Error: no earlier data available for " << date << std::endl;
            continue;
        }

        double result = value * it->second;
        std::cout << date << " => " << std::fixed << std::setprecision(2)
                  << value << " = " << result << std::endl;
    }
}
