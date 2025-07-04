/**
 * @file replacer_configurer.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Configurer for the Replacer
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include "travesim_adapters/configurers/replacer_configurer.hpp"
#include "travesim_adapters/configurers/configurers_utils.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define REPLACER_CONFIGURER_NAMESPACE BASE_CONFIGURER_NAMESPACE "replacer"

namespace travesim {
/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

ReplacerConfigurer::ReplacerConfigurer(void) : AdapterConfigurer<travesim_adapters::ReplacerConfig>::AdapterConfigurer(
        REPLACER_CONFIGURER_NAMESPACE) {
}

std::string ReplacerConfigurer::get_address(void) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);

    std::string address = this->config.replacer_address;

    IPValidation validation = check_valid_ip(address, MIN_UNICAST_ADDRESS, MAX_UNICAST_ADDRESS);

    if (validation == IPValidation::VALID) {
        return address;
    } else {
        ROS_ERROR_STREAM(get_error_msg(validation));

        return INVALID_ADDRESS;
    }
}

uint16_t ReplacerConfigurer::get_port(void) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);
    return this->config.replacer_port;
}

bool ReplacerConfigurer::get_specific_source(void) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);
    return this->config.specific_source;
}

std::ostream& operator <<(std::ostream& output, const ReplacerConfigurer& repl_conf) {
    output << "Replacer Endpoint: " << repl_conf.config.replacer_address;
    output << ":" << repl_conf.config.replacer_port << std::endl;
    output << "Specific Source: " << (repl_conf.config.specific_source ? "True" : "False") << std::endl;
    output << "Reset: " << ((repl_conf.config.reset || repl_conf.reconfigured) ? "True" : "False") << std::endl;

    return output;
}
}
