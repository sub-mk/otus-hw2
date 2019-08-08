#include "gtest/gtest.h"

#include "lib.h"

class LibTest : public::testing::Test {};

TEST_F(LibTest, PrintIp) {
    auto ip_pool = std::vector<std::vector<int>>{
        {12, 13, 14, 15},
        {22, 23, 24, 25}
    };
    testing::internal::CaptureStdout();
    lib::print_ip(ip_pool);
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_TRUE( output == std::string("12.13.14.15\n22.23.24.25\n") );
}

TEST_F(LibTest, Str2Int) {
    std::vector<std::string> str_vec{"11", "22", "33"};
    auto int_vec = lib::str2int(str_vec);
    ASSERT_TRUE( (int_vec == std::vector<int>{11, 22, 33}) );
}

TEST_F(LibTest, SortRevLex) {
    lib::IpPool ip_pool = { {113, 162, 145, 156},
                            {157, 39, 22, 224},
                            {79, 180, 73, 190} };
    auto sorted_pool = lib::sort_rev_lex(ip_pool);
    lib::IpPool output = { {157, 39, 22, 224},
                            {113, 162, 145, 156},
                            {79, 180, 73, 190} };
    ASSERT_TRUE( (output == sorted_pool) );
}

TEST_F(LibTest, FilterByte) {
    lib::IpPool ip_pool = { {113, 162, 145, 156},
                            {157, 39, 22, 224},
                            {157, 180, 73, 190} };
    auto filtered_pool = lib::filter_first_bytes(ip_pool, 157);
    lib::IpPool output = { {157, 39, 22, 224},
                           {157, 180, 73, 190} };
    ASSERT_TRUE( (output == filtered_pool) );
}

TEST_F(LibTest, FilterAny) {
    lib::IpPool ip_pool = { {113, 162, 145, 156},
                            {157, 39, 22, 224},
                            {79, 22, 73, 190} };
    auto filtered_pool = lib::filter_any_byte(ip_pool, 22);
    lib::IpPool output = { {157, 39, 22, 224},
                           {79, 22, 73, 190}};
    ASSERT_TRUE( (output == filtered_pool) );
}
