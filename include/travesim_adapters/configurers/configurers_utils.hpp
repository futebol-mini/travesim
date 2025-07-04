/**
 * @file configurers_utils.hpp
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

#include <string>
#include <sstream>

/*****************************************
 * Public Constants
 *****************************************/

#define MIN_UNICAST_ADDRESS "127.0.0.0"
#define MAX_UNICAST_ADDRESS "127.255.255.255"

#define MIN_MULTICAST_ADDRESS "224.0.0.0"
#define MAX_MULTICAST_ADDRESS "239.255.255.255"

#define INVALID_ADDRESS "0.0.0.0"

namespace travesim {
/*****************************************
 * Public Types
 *****************************************/

/**
 * @brief Type used to validate a IP string
 */
enum IPValidation {
    VALID,           /**< Valid IP address */
    INVALID_FORMAT,  /**< Wrong formatted IP string */
    INVALID_NUMBERS, /**< The numbers on the ip are not representable by 8 bits */
    OUT_OF_RANGE     /**< The IP is not in the specified range */
};

/*****************************************
 * Public Funtions Prototypes
 *****************************************/

/**
 * @brief Converts a IPv4 in a string to a array of unsigned integers,
 *        where the most significant byte of the IP address is in the
 *        position 0 and the last significant in the position 3.
 *
 * @note Expects IPv4 in the quad-dotted notation.
 *
 * @param ip_string IPv4 string to be converted
 * @param ip_uint Pointer where to store the converted IPv4
 *
 * @return true if the conversion was successful, false otherwise
 */
bool ipv4_string_to_uint(std::string ip_string, uint* ip_uint);

/**
 * @brief Checks if a IP is valid and is in the specified range
 *
 * @note Expects IPv4 in the quad-dotted notation.
 *
 * @param ip IP string to be converted
 * @param min_ip Minimum IP interval value
 * @param max_ip Maximum IP interval value
 *
 * @return @ref IPValidation
 */
IPValidation check_valid_ip(std::string ip, std::string min_ip, std::string max_ip);

/**
 * @brief Get the error msg based on the validation type
 *
 * @param error Which error to get the message
 *
 * @return std::string representing the error
 */
std::string get_error_msg(IPValidation error);
}  // namespace travesim
