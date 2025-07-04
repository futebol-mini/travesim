/**
 * @file field_command.hpp
 *
 * @brief Field state data structure
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 04/2021
 */

#ifndef __FIELD_STATE_H__
#define __FIELD_STATE_H__

#include <vector>
#include <iostream>

#include "travesim_adapters/data/data_common.hpp"
#include "travesim_adapters/data/entity_state.hpp"

namespace travesim {
/**
 * @brief Data structure to hold the field state
 *
 */
class FieldState {
    public:
        /**
         * @brief Construct a new Field State object
         *
         * @param teams_formation Number of robots per team, default is 3
         */
        FieldState(TeamsFormation teams_formation = TeamsFormation::THREE_ROBOTS_PER_TEAM);

        /**
         * @brief Output stream operator overloading
         *
         */
        friend std::ostream& operator <<(std::ostream& output, const FieldState& field_state);

        uint time_step;  /**< ODE time step */

        uint8_t robots_per_team;

        /**
         * @brief Field entities
         *
         */
        EntityState ball;

        std::vector<EntityState> yellow_team;
        std::vector<EntityState> blue_team;
};
}

#endif // __FIELD_STATE_H__
