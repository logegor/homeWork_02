#include <cassert>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <assert.h>



union IP{
    uint8_t oct1;
    uint8_t oct2;
};
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<std::string> filter(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

//int main(int argc, char const *argv[])
int main()
{
    try
    {
        std::vector<std::vector<std::string> > ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
            assert(ip_pool.back().size() == 4);
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), [](std::vector<std::string>& first, std::vector<std::string>& second) -> bool
                                                    {
                                                        if (std::stoi(first.at(0)) > std::stoi(second.at(0)))
                                                            return true;
                                                        if (std::stoi(first.at(0)) == std::stoi(second.at(0)) && 
                                                            std::stoi(first.at(1)) > std::stoi(second.at(1)))
                                                            return true;
                                                        if (std::stoi(first.at(0)) == std::stoi(second.at(0)) && 
                                                            std::stoi(first.at(1)) == std::stoi(second.at(1)) &&
                                                            std::stoi(first.at(2)) > std::stoi(second.at(2)))
                                                            return true;
                                                        if (std::stoi(first.at(0)) == std::stoi(second.at(0)) && 
                                                            std::stoi(first.at(1)) == std::stoi(second.at(1)) &&
                                                            std::stoi(first.at(2)) == std::stoi(second.at(2)) &&
                                                            std::stoi(first.at(3)) > std::stoi(second.at(3)))
                                                            return true;
                                                        return false;
                                                    });

        for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        auto filter = [ip_pool](uint16_t oct1 = 0xFFFF, uint16_t oct2 = 0xFFFF, uint16_t oct3 = 0xFFFF, uint16_t oct4 = 0xFFFF)
                        {
                            assert (oct1 != 0xFFFF || oct2 != 0xFFFF || oct3 != 0xFFFF || oct4 != 0xFFFF);
                            std::for_each(ip_pool.cbegin(), ip_pool.cend(), [oct1, oct2, oct3, oct4](auto& it)
                                                                            {
                                                                                if ((std::stoi(it.at(0)) == oct1 || oct1 == 0xFFFF) && 
                                                                                    (std::stoi(it.at(1)) == oct2 || oct2 == 0xFFFF) &&
                                                                                    (std::stoi(it.at(2)) == oct3 || oct3 == 0xFFFF) && 
                                                                                    (std::stoi(it.at(3)) == oct4 || oct4 == 0xFFFF))
                                                                                {
                                                                                    for(std::vector<std::string>::const_iterator ip_part = it.cbegin(); ip_part != it.cend(); ++ip_part)
                                                                                    {
                                                                                        if (ip_part != it.cbegin())
                                                                                        {
                                                                                            std::cout << ".";

                                                                                        }
                                                                                        std::cout << *ip_part;
                                                                                    }
                                                                                    std::cout << std::endl;
                                                                                }
                                                                            });
                        };
        auto filter_any = [ip_pool](uint16_t oct)
                        {
                            std::for_each(ip_pool.cbegin(), ip_pool.cend(), [oct](auto& it)
                                                                            {
                                                                                if ((std::stoi(it.at(0)) == oct) ||
                                                                                    (std::stoi(it.at(1)) == oct) ||
                                                                                    (std::stoi(it.at(2)) == oct) ||
                                                                                    (std::stoi(it.at(3)) == oct))
                                                                                {
                                                                                    for(std::vector<std::string>::const_iterator ip_part = it.cbegin(); ip_part != it.cend(); ++ip_part)
                                                                                    {
                                                                                        if (ip_part != it.cbegin())
                                                                                        {
                                                                                            std::cout << ".";

                                                                                        }
                                                                                        std::cout << *ip_part;
                                                                                    }
                                                                                    std::cout << std::endl;
                                                                                }
                                                                            });
                        };
        filter(1);      
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        filter(46,70);
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        filter_any(46);
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
