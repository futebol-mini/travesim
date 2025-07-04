/**
 * @file teams_configurer.cpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Configurer for the teams
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include "travesim_adapters/configurers/teams_configurer.hpp"
#include "travesim_adapters/configurers/configurers_utils.hpp"

/*****************************************
 * Private Constants
 *****************************************/

#define TEAMS_CONFIGURER_NAMESPACE BASE_CONFIGURER_NAMESPACE "teams"

namespace travesim {
/*****************************************
 * Public Methods Bodies Definitions
 *****************************************/

TeamsConfigurer::TeamsConfigurer(void) : AdapterConfigurer<travesim_adapters::TeamsConfig>::AdapterConfigurer(
        TEAMS_CONFIGURER_NAMESPACE) {
}

std::string TeamsConfigurer::get_address(TeamColor color) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);

    std::string address;

    if (color == TeamColor::YELLOW) {
        address = this->config.yellow_team_address;
    } else {
        address = this->config.blue_team_address;
    }

    IPValidation validation = check_valid_ip(address, MIN_UNICAST_ADDRESS, MAX_UNICAST_ADDRESS);

    if (validation == IPValidation::VALID) {
        return address;
    } else {
        ROS_ERROR_STREAM(get_error_msg(validation));

        return INVALID_ADDRESS;
    }
}

uint16_t TeamsConfigurer::get_port(TeamColor color) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);

    if (color == TeamColor::YELLOW) {
        return this->config.yellow_team_port;
    } else {
        return this->config.blue_team_port;
    }
}

bool TeamsConfigurer::get_specific_source(void) {
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);
    return this->config.specific_source;
}

std::ostream& operator <<(std::ostream& output, const TeamsConfigurer& teams_conf) {
    output << "Yellow Team Endpoint: " << teams_conf.config.yellow_team_address;
    output << ":" << teams_conf.config.yellow_team_port << std::endl;
    output << "Blue Team Endpoint: " << teams_conf.config.blue_team_address;
    output << ":" << teams_conf.config.blue_team_port << std::endl;
    output << "Specific Source: " << (teams_conf.config.specific_source ? "True" : "False") << std::endl;
    output << "Reset: " << ((teams_conf.config.reset || teams_conf.reconfigured) ? "True" : "False") << std::endl;

    return output;
}
}
