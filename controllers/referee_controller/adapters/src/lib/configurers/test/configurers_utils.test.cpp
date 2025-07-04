/**
 * @file configurers_utils.test.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Test configurers utilitary functions
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <ros/ros.h>
#include <gtest/gtest.h>

#include "travesim_adapters/configurers/configurers_utils.hpp"

/*****************************************
 * Test functions
 *****************************************/

TEST(configurers_utils, ipv4_string_to_uint)
{
    uint ip_uint[4] = {0};

    EXPECT_TRUE(travesim::ipv4_string_to_uint("1.1.1.1", ip_uint));
    EXPECT_TRUE(testing::internal::ArrayEq(ip_uint, {1, 1, 1, 1}));

    ip_uint[0] = 0;
    ip_uint[1] = 0;
    ip_uint[2] = 0;
    ip_uint[3] = 0;

    EXPECT_TRUE(travesim::ipv4_string_to_uint("127.220.4.32", ip_uint));
    EXPECT_TRUE(testing::internal::ArrayEq(ip_uint, {127, 220, 4, 32}));

    ip_uint[0] = 0;
    ip_uint[1] = 0;
    ip_uint[2] = 0;
    ip_uint[3] = 0;

    EXPECT_FALSE(travesim::ipv4_string_to_uint("@.b.C.3", ip_uint));
    EXPECT_TRUE(testing::internal::ArrayEq(ip_uint, {0, 0, 0, 0}));

    ip_uint[0] = 0;
    ip_uint[1] = 0;
    ip_uint[2] = 0;
    ip_uint[3] = 0;

    EXPECT_FALSE(travesim::ipv4_string_to_uint("123,123,123,123", ip_uint));
    EXPECT_TRUE(testing::internal::ArrayEq(ip_uint, {123, 0, 0, 0}));

    ip_uint[0] = 0;
    ip_uint[1] = 0;
    ip_uint[2] = 0;
    ip_uint[3] = 0;

    EXPECT_FALSE(travesim::ipv4_string_to_uint("Test", ip_uint));
    EXPECT_TRUE(testing::internal::ArrayEq(ip_uint, {0, 0, 0, 0}));

    ip_uint[0] = 0;
    ip_uint[1] = 0;
    ip_uint[2] = 0;
    ip_uint[3] = 0;

    EXPECT_FALSE(travesim::ipv4_string_to_uint("239.64.73.Q", ip_uint));
    EXPECT_TRUE(testing::internal::ArrayEq(ip_uint, {239, 64, 73, 0}));
}

TEST(configurers_utils, check_valid_ip)
{
    using namespace travesim;

    EXPECT_EQ(check_valid_ip("127.0.0.2", "127.0.0.0", "127.255.255.0"), IPValidation::VALID);
    EXPECT_EQ(check_valid_ip("225.0.64.2", "224.0.0.0", "239.255.34.255"), IPValidation::VALID);
    EXPECT_EQ(check_valid_ip("227.0.0.2", "227.0.0.0", "A.255.255.0"), IPValidation::INVALID_FORMAT);
    EXPECT_EQ(check_valid_ip("127.0.0,2", "127.0.0.0", "127.255.255.0"), IPValidation::INVALID_FORMAT);
    EXPECT_EQ(check_valid_ip("127.0.512.2", "127.0.0.0", "127.255.255.0"), IPValidation::INVALID_NUMBERS);
    EXPECT_EQ(check_valid_ip("1024.0.0.2", "127.0.0.0", "127.255.255.0"), IPValidation::INVALID_NUMBERS);
    EXPECT_EQ(check_valid_ip("127.0.0.2", "127.0.0.255", "127.255.255.0"), IPValidation::OUT_OF_RANGE);
    EXPECT_EQ(check_valid_ip("224.0.0.2", "127.0.0.0", "127.255.255.0"), IPValidation::OUT_OF_RANGE);
}

TEST(configurers_utils, get_error_msg)
{
    using namespace travesim;

    EXPECT_EQ(get_error_msg(IPValidation::VALID), "No error.");
    EXPECT_EQ(get_error_msg(IPValidation::INVALID_FORMAT), "The IP string is wrong formatted.");
    EXPECT_EQ(get_error_msg(IPValidation::INVALID_NUMBERS),
              "The numbers on the ip are not representable by 8 bits.");
    EXPECT_EQ(get_error_msg(IPValidation::OUT_OF_RANGE),
              "The IP is not in the specified range. Hover over the parameterto see the range.");
    EXPECT_EQ(get_error_msg(IPValidation(42)), "No error.");
}

// Run all the tests that were declared with TEST()
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
