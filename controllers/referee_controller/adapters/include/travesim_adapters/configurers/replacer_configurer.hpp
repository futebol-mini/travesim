/**
 * @file replacer_configurer.hpp
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

#include <iostream>

#include <travesim_adapters/ReplacerConfig.h>

#include "travesim_adapters/configurers/adapter_configurer.hpp"

#ifndef __REPLACER_CONFIGURER_H__
#define __REPLACER_CONFIGURER_H__

namespace travesim {
/**
 * @brief ReplacerConfigurer class definition
 */

class ReplacerConfigurer :
    public AdapterConfigurer<travesim_adapters::ReplacerConfig> {
    public:
        /**
         * @brief Construct a new ReplacerConfigurer object
         */
        ReplacerConfigurer(void);

        /**
         * @brief Get the replacer configured address
         *
         * @return std::string address string
         */
        std::string get_address(void);

        /**
         * @brief Get the replacer configured port
         *
         * @return uint16_t port number
         */
        uint16_t get_port(void);

        /**
         * @brief Get the specific_source config
         *
         * @return true if specific source is enabled, false otherwise
         */
        bool get_specific_source(void);

        /**
         * @brief Output stream operator overloading
         */
        friend std::ostream& operator <<(std::ostream& output, const ReplacerConfigurer& repl_conf);
};
}  // namespace travesim

#endif // __REPLACER_CONFIGURER_H__
