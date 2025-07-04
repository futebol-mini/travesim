/**
 * @file vision_configurer.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Configurer for the vision
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include "travesim_adapters/configurers/vision_configurer.hpp"
#include "travesim_adapters/configurers/configurers_utils.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define VISION_CONFIGURER_NAMESPACE BASE_CONFIGURER_NAMESPACE "vision"

namespace travesim {
/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

VisionConfigurer::VisionConfigurer(void) : AdapterConfigurer<travesim_adapters::VisionConfig>::AdapterConfigurer(
        VISION_CONFIGURER_NAMESPACE) {
}

std::string VisionConfigurer::get_address(void) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);

    std::string address = this->config.multicast_address;

    IPValidation validation = check_valid_ip(address, MIN_MULTICAST_ADDRESS, MAX_MULTICAST_ADDRESS);

    if (validation == IPValidation::VALID) {
        return address;
    } else {
        ROS_ERROR_STREAM(get_error_msg(validation));

        return INVALID_ADDRESS;
    }
}

uint16_t VisionConfigurer::get_port(void) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);
    return this->config.multicast_port;
}

std::ostream& operator <<(std::ostream& output, const VisionConfigurer& vision_conf) {
    output << "Vision Endpoint: " << vision_conf.config.multicast_address;
    output << ":" << vision_conf.config.multicast_port << std::endl;
    output << "Reset: " << ((vision_conf.config.reset || vision_conf.reconfigured) ? "True" : "False") << std::endl;

    return output;
}
}
