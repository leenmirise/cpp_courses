#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using Vec = std::vector<std::vector<std::string> > ;

bool compare(const std::vector<std::string>& left, const std::vector<std::string>& right)
{
    for(size_t i = 0; i < size(left); i++){
        if (left[i] > right[i]) return true;
    }
    return false;
}

void filterFirstByte(const Vec& vec){
    for(auto& i : vec){
        if(i[0] == "1"){
            for(auto ip_part = i.cbegin(); ip_part != i.cend(); ++ip_part)
            {
                if (ip_part != i.cbegin()) std::cout << ".";
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
}

void filterFirstAndSecondBytes(const Vec& vec){
    for(auto& i : vec){
        if(i[0] == "46" && i[1] == "70"){
            for(auto ip_part = i.cbegin(); ip_part != i.cend(); ++ip_part)
            {
                if (ip_part != i.cbegin()) std::cout << ".";
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
    }
}

void filterAnyByte(const Vec& vec){
    for(auto& i : vec){
        for(auto& j : i){
            if(j == "46"){
                for(auto ip_part = i.cbegin(); ip_part != i.cend(); ++ip_part)
                {
                    if (ip_part != i.cbegin()) std::cout << ".";
                    std::cout << *ip_part;
                }
                std::cout << std::endl;
                break;
            }
        }
    }
}

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

int main()
{
    try
    {
        Vec ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort

        std::sort(begin(ip_pool), end(ip_pool), compare);

        for(const auto & ip : ip_pool)
        {
            for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
            {
                if (ip_part != ip.cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        // TODO filter by first byte and output
        filterFirstByte(ip_pool);

        // TODO filter by first and second bytes and output
        filterFirstAndSecondBytes(ip_pool);

        // TODO filter by any byte and output
        filterAnyByte(ip_pool);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
