/**
 * @file data_common.hpp
 *
 * @brief Common constants and types for the data structures
 *
 * @author Lucas Haug <lucas.haug@thunderatz.org>
 *
 * @date 06/2021
 */

#ifndef __DATA_COMMON_H__
#define __DATA_COMMON_H__

/*****************************************
 * Public Constants
 *****************************************/

/**
 * @brief Printing output configuration constants
 */
#define PRINTING_MIN_WIDTH 6U
#define PRINTING_DECIMAL_PRECISION 3U

/**
 * @brief Field and goal constants
 */
#define FIELD_WIDTH_M 1.3F
#define FIELD_LENGTH_M 1.5F
#define GOAL_WIDTH_M 0.4F
#define GOAL_DEPTH_M 0.1F

/*****************************************
 * Public Types
 *****************************************/

namespace travesim {
/**
 * @brief Formation of the teams
 */
enum TeamsFormation {
    THREE_ROBOTS_PER_TEAM = 3,
    FIVE_ROBOTS_PER_TEAM = 5,
};
}

#endif // __DATA_COMMON_H__
