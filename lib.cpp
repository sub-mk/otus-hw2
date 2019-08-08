#include "lib.h"

namespace lib {

    std::vector<std::string> split(const std::string &str, char d) {
        // ("",  '.') -> [""]
        // ("11", '.') -> ["11"]
        // ("..", '.') -> ["", "", ""]
        // ("11.", '.') -> ["11", ""]
        // (".11", '.') -> ["", "11"]
        // ("11.22", '.') -> ["11", "22"]
        std::vector<std::string> r;

        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        while (stop != std::string::npos) {
            r.push_back(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }
        r.push_back(str.substr(start));
        return r;
    }

    std::vector<int> str2int(const std::vector<std::string> &str) {
        std::vector<int> int_vec(str.size());
        std::transform(str.begin(), str.end(), int_vec.begin(),
                       [](const std::string& s) { return std::stoi(s); });
        return int_vec;
    }

    void print_ip(const IpPool &ip_pool) {
        for(auto& ip: ip_pool) {
            for (auto it = ip.cbegin(); it != ip.cend(); ++it) {
                if (it != ip.cbegin()) {
                    std::cout << ".";
                }
                std::cout << *it;
            }
            std::cout << std::endl;
        }
    }

    IpPool sort_rev_lex(IpPool &ip_pool) {
        auto sorted_vec = ip_pool;
        auto comp = [] (const lib::IpList& x, const lib::IpList& y){
            if (x[0] == y[0]) {
                if (x[1] == y[1]) {
                    return x[2] == y[2] ? x[3] > y[3] : x[2] > y[2];
                } else {
                    return x[1] > y[1];
                }
            } else {
                return x[0] > y[0];
            }
        };
        std::sort(sorted_vec.begin(), sorted_vec.end(), comp);
        return sorted_vec;
    }

    IpPool filter_first_bytes(IpPool &ip_pool, int first_byte, int second_byte) {
        IpPool first_byte_vec;
        std::copy_if (ip_pool.begin(), ip_pool.end(), std::back_inserter(first_byte_vec),
                [first_byte, second_byte](IpList ip){ return second_byte == -1 ? ip[0] == first_byte : ip[0] == first_byte && ip[1] == second_byte; }
                );
        return first_byte_vec;
    }

    IpPool filter_any_byte(IpPool &ip_pool, int byte) {
        IpPool filter_byte_vec;
        std::copy_if (ip_pool.begin(), ip_pool.end(), std::back_inserter(filter_byte_vec),
                      [byte](IpList ip){ return ip[0] == byte || ip[1] == byte || ip[2] == byte || ip[3] == byte; }
        );
        return filter_byte_vec;
    }

}