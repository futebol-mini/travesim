/**
 * @file teams_configurer.hpp
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

#include <iostream>

#include <travesim_adapters/TeamsConfig.h>

#include "travesim_adapters/configurers/adapter_configurer.hpp"

#ifndef __TEAMS_CONFIGURER_H__
#define __TEAMS_CONFIGURER_H__

namespace travesim {
/**
 * @brief TeamsConfigurer class definition
 */

class TeamsConfigurer :
    public AdapterConfigurer<travesim_adapters::TeamsConfig> {
    public:
        /**
         * @brief Team color enumeration type
         */
        enum TeamColor {
            YELLOW,
            BLUE
        };

        /**
         * @brief Construct a new TeamsConfigurer object
         */
        TeamsConfigurer(void);

        /**
         * @brief Get the configured address of a team
         *
         * @param color Color of the team to get the address
         *
         * @return std::string address string
         */
        std::string get_address(TeamColor color);

        /**
         * @brief Get the configured port of a team
         *
         * @param color Color of the team to get the port
         *
         * @return uint16_t port number
         */
        uint16_t get_port(TeamColor color);

        /**
         * @brief Get the specific_source config
         *
         * @return true if specific source is enabled, false otherwise
         */
        bool get_specific_source(void);

        /**
         * @brief Output stream operator overloading
         */
        friend std::ostream& operator <<(std::ostream& output, const TeamsConfigurer& teams_conf);
};
}  // namespace travesim

#endif // __TEAMS_CONFIGURER_H__
