#ifndef IP_FILTER_LIB_H
#define IP_FILTER_LIB_H

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace lib {

    using IpList = std::vector<int>;
    using IpPool = std::vector<IpList>;

    std::vector<std::string> split(const std::string &str, char d);

    std::vector<int> str2int(const std::vector<std::string> &str);

    void print_ip(const IpPool &ip_pool);

    IpPool sort_rev_lex(IpPool &ip_pool);

    IpPool filter_first_bytes(IpPool &ip_pool, int first_byte, int second_byte = -1);

    IpPool filter_any_byte(IpPool &ip_pool, int byte);

}

#endif //IP_FILTER_LIB_H
