/**
 * @file adapter_configurer.hpp
 *
 * @author Lucas Haug <lucas.haug@thuneratz.org>
 *
 * @brief Template configurer for an adapter
 *
 * @date 06/2021
 *
 * @copyright MIT License - Copyright (c) 2021 ThundeRatz
 *
 */

#include <memory>

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <boost/thread/recursive_mutex.hpp>

#ifndef __ADAPTER_CONFIGURER_H__
#define __ADAPTER_CONFIGURER_H__

/*****************************************
 * Public Constants
 *****************************************/

#define BASE_CONFIGURER_NAMESPACE "travesim_adapters/"

namespace travesim {
/*****************************************
 * Class Definition
 *****************************************/

template <class AdapterConfigType>
class AdapterConfigurer {
    public:
        /**
         * @brief Construct a new AdapterConfigurer object
         *
         * @note The base namespace is used
         */
        AdapterConfigurer(void);

        /**
         * @brief Construct a new AdapterConfigurer object
         *
         * @param config_namespace Namespace of the adapter configurer
         */
        AdapterConfigurer(std::string config_namespace);

        /**
         * @brief Get the reset config
         *
         * @return true if should reset, false otherwise
         */
        bool get_reset(void);

    protected:
        bool reconfigured;  /**< Whether the configs where changed or not */

        AdapterConfigType config;  /**< Current config */

        boost::recursive_mutex mutex;  /**< Dynamic Reconfigure Server Mutex for thread-safety */

    private:
        std::unique_ptr<ros::NodeHandle> node_handle;  /**< Pointer to ROS Node Handle */

        std::unique_ptr<dynamic_reconfigure::Server<AdapterConfigType>> server;  /**< Dynamic Reconfigure Server */

        /**
         * @brief Dynamic Reconfigure Server Callback
         *
         * @param config New config received
         * @param level Result of doing an "OR" operation between all of
         *              level values of the parameters that have changed
         */
        void callback(AdapterConfigType& config, uint32_t level);
};

/*****************************************
 * Class Public Methods Implementation
 *****************************************/

template <class AdapterConfigType>
AdapterConfigurer<AdapterConfigType>::AdapterConfigurer() : AdapterConfigurer(
        BASE_CONFIGURER_NAMESPACE) {
}

template <class AdapterConfigType>
AdapterConfigurer<AdapterConfigType>::AdapterConfigurer(std::string config_namespace) {
    this->reconfigured = false;

    this->node_handle = std::unique_ptr<ros::NodeHandle>(new ros::NodeHandle(config_namespace));

    using server_t = dynamic_reconfigure::Server<AdapterConfigType>;
    this->server = std::unique_ptr<server_t>(new server_t(this->mutex, *(this->node_handle)));

    typename server_t::CallbackType server_cb;
    server_cb = boost::bind(&AdapterConfigurer::callback, this, _1, _2);
    this->server->setCallback(server_cb);

    // Update the default config in the dynamic reconfigurer
    boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);
    this->server->getConfigDefault(this->config);
    this->server->updateConfig(this->config);
}

template <class AdapterConfigType>
bool AdapterConfigurer<AdapterConfigType>::get_reset(void) {
    bool should_reset = this->config.reset || this->reconfigured;

    if (should_reset) {
        boost::recursive_mutex::scoped_lock scoped_lock(this->mutex);

        this->reconfigured = false;

        this->config.reset = this->reconfigured;

        this->server->updateConfig(this->config);

        return true;
    }

    return false;
}

/*****************************************
 * Class Private Methods Implementation
 *****************************************/

template <class AdapterConfigType>
void AdapterConfigurer<AdapterConfigType>::callback(AdapterConfigType& config, uint32_t level) {
    this->config = config;
    this->reconfigured = true;
}
}  // namespace travesim

#endif // __ADAPTER_CONFIGURER_H__
