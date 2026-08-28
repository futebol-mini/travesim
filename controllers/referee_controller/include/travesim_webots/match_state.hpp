/**
 * @file match_state.hpp
 *
 * @brief Match clock, score and goal-line crossing detection.
 *
 * @copyright MIT License - Copyright (c) 2026 Futebol Mini
 */

#ifndef TRAVESIM_WEBOTS_MATCH_STATE_HPP
#define TRAVESIM_WEBOTS_MATCH_STATE_HPP

#include <cstdint>

#include "travesim_adapters/data/entity_state.hpp"

namespace travesim::webots_adapter {

enum class ScoringTeam {
    NONE,
    BLUE,
    YELLOW,
};

class MatchState {
    public:
        explicit MatchState(double duration_seconds);

        ScoringTeam observe_ball(const travesim::Vector2D& position);
        void synchronize_ball(const travesim::Vector2D& position);
        bool is_finished(double elapsed_seconds) const;

        uint32_t goals_blue() const;
        uint32_t goals_yellow() const;

    private:
        double duration_seconds;
        bool has_previous_ball_position;
        travesim::Vector2D previous_ball_position;
        uint32_t blue_score;
        uint32_t yellow_score;
};

}  // namespace travesim::webots_adapter

#endif  // TRAVESIM_WEBOTS_MATCH_STATE_HPP
