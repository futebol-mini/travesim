/**
 * @file vision_configurer.hpp
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

#include <iostream>

#include <travesim_adapters/VisionConfig.h>

#include "travesim_adapters/configurers/adapter_configurer.hpp"

#ifndef __VISION_CONFIGURER_H__
#define __VISION_CONFIGURER_H__

namespace travesim {
/**
 * @brief VisionConfigurer class definition
 */

class VisionConfigurer :
    public AdapterConfigurer<travesim_adapters::VisionConfig> {
    public:
        /**
         * @brief Construct a new VisionConfigurer object
         */
        VisionConfigurer(void);

        /**
         * @brief Get the vision configured address
         *
         * @return std::string address string
         */
        std::string get_address(void);

        /**
         * @brief Get the vision configured port
         *
         * @return uint16_t port number
         */
        uint16_t get_port(void);

        /**
         * @brief Output stream operator overloading
         */
        friend std::ostream& operator <<(std::ostream& output, const VisionConfigurer& vision_conf);
};
}  // namespace travesim

#endif // __VISION_CONFIGURER_H__
