/**
 * @file configurers_utils.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Configurers utilitary funtions
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include "travesim_adapters/configurers/configurers_utils.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define IPV4_NUM_OF_BYTES 4U

/*****************************************
 * Public Funtions Bodies Definitions
 *****************************************/

namespace travesim {
bool ipv4_string_to_uint(std::string ip_string, uint* ip_uint) {
    std::stringstream ip_stream(ip_string);

    char dot;

    if (ip_stream.rdbuf()->in_avail() == 0) {
        return false;
    } else {
        ip_stream >> ip_uint[0];

        if (ip_stream.fail()) {
            return false;
        }
    }

    for (uint i = 1; i < IPV4_NUM_OF_BYTES; i++) {
        if (ip_stream.rdbuf()->in_avail() == 0) {
            return false;
        } else {
            ip_stream >> dot;

            if (ip_stream.fail()) {
                return false;
            }

            if (dot != '.') {
                return false;
            }
        }

        if (ip_stream.rdbuf()->in_avail() == 0) {
            return false;
        } else {
            ip_stream >> ip_uint[i];

            if (ip_stream.fail()) {
                return false;
            }
        }
    }

    if (ip_stream.rdbuf()->in_avail() != 0) {
        return false;
    }

    return true;
}

IPValidation check_valid_ip(std::string ip, std::string min_ip, std::string max_ip) {
    uint ip_uint[IPV4_NUM_OF_BYTES] = {0};
    uint min_ip_uint[IPV4_NUM_OF_BYTES] = {0};
    uint max_ip_uint[IPV4_NUM_OF_BYTES] = {0};

    // Check formats
    if (!ipv4_string_to_uint(ip, ip_uint)) {
        return IPValidation::INVALID_FORMAT;
    }

    if (!ipv4_string_to_uint(min_ip, min_ip_uint)) {
        return IPValidation::INVALID_FORMAT;
    }

    if (!ipv4_string_to_uint(max_ip, max_ip_uint)) {
        return IPValidation::INVALID_FORMAT;
    }

    // Check numbers
    for (uint i = 0; i < IPV4_NUM_OF_BYTES; i++) {
        if (ip_uint[i] > 0xFF) {
            return IPValidation::INVALID_NUMBERS;
        }

        if (min_ip_uint[i] > 0xFF) {
            return IPValidation::INVALID_NUMBERS;
        }

        if (max_ip_uint[i] > 0xFF) {
            return IPValidation::INVALID_NUMBERS;
        }
    }

    // Check range
    uint32_t ip_num = 0;
    uint32_t max_num = 0;
    uint32_t min_num = 0;

    for (uint8_t i = 0; i < IPV4_NUM_OF_BYTES; i++) {
        ip_num = ip_num << 8;
        ip_num += ip_uint[i];
        min_num = min_num << 8;
        min_num += min_ip_uint[i];
        max_num = max_num << 8;
        max_num += max_ip_uint[i];
    }

    if ((ip_num < min_num) || (ip_num > max_num)) {
        return IPValidation::OUT_OF_RANGE;
    }

    return IPValidation::VALID;
}

std::string get_error_msg(IPValidation error) {
    switch (error) {
        case (IPValidation::INVALID_FORMAT): {
            return "The IP string is wrong formatted.";
        }

        case (IPValidation::INVALID_NUMBERS): {
            return "The numbers on the ip are not representable by 8 bits.";
        }

        case (IPValidation::OUT_OF_RANGE): {
            return "The IP is not in the specified range. Hover over the parameterto see the range.";
        }

        default: {
            return "No error.";
        }
    }
}
}
