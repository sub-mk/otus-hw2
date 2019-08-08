#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "lib.h"

int main(/*int argc, char const *argv[]*/)
{
    try
    {
        lib::IpPool ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = lib::split(line, '\t');
            ip_pool.push_back(lib::str2int(lib::split(v.at(0), '.')));
        }

        // reverse lexicographically sort
        auto rev_lex_pool = lib::sort_rev_lex(ip_pool);
        lib::print_ip(rev_lex_pool);

        // filter by first byte and output
        auto filter_pool_1 = lib::filter_first_bytes(rev_lex_pool, 1);
        lib::print_ip(filter_pool_1);

        // filter by first and second bytes and output
        auto filter_pool_2 = lib::filter_first_bytes(rev_lex_pool, 46, 70);
        lib::print_ip(filter_pool_2);

        // filter by any byte and output
        auto filter_pool_3 = lib::filter_any_byte(rev_lex_pool, 46);
        lib::print_ip(filter_pool_3);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

