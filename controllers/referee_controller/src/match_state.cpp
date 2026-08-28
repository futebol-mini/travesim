/**
 * @file match_state.cpp
 *
 * @brief Match clock, score and goal-line crossing detection.
 *
 * @copyright MIT License - Copyright (c) 2026 Futebol Mini
 */

#include <cmath>

#include "travesim_adapters/data/data_common.hpp"
#include "travesim_webots/match_state.hpp"

namespace travesim::webots_adapter {
namespace {

bool crosses_goal_line(
    const travesim::Vector2D& previous,
    const travesim::Vector2D& current,
    double goal_line_x,
    bool positive_direction) {
    const bool crossed = positive_direction
        ? previous.x < goal_line_x && current.x >= goal_line_x
        : previous.x > goal_line_x && current.x <= goal_line_x;

    if (!crossed) {
        return false;
    }

    const double delta_x = current.x - previous.x;
    if (delta_x == 0.0) {
        return false;
    }

    const double interpolation = (goal_line_x - previous.x) / delta_x;
    const double crossing_y = previous.y + interpolation * (current.y - previous.y);
    return std::abs(crossing_y) <= GOAL_WIDTH_M / 2.0;
}

}  // namespace

MatchState::MatchState(double duration_seconds) :
    duration_seconds(duration_seconds),
    has_previous_ball_position(false),
    previous_ball_position(0.0, 0.0),
    blue_score(0),
    yellow_score(0) { }

ScoringTeam MatchState::observe_ball(const travesim::Vector2D& position) {
    ScoringTeam scoring_team = ScoringTeam::NONE;

    if (this->has_previous_ball_position) {
        const double positive_goal_line = FIELD_LENGTH_M / 2.0;
        const double negative_goal_line = -positive_goal_line;

        // Blue starts on the negative-x side and attacks the positive-x goal.
        if (crosses_goal_line(this->previous_ball_position, position, positive_goal_line, true)) {
            this->blue_score++;
            scoring_team = ScoringTeam::BLUE;
        } else if (crosses_goal_line(this->previous_ball_position, position, negative_goal_line, false)) {
            this->yellow_score++;
            scoring_team = ScoringTeam::YELLOW;
        }
    }

    this->synchronize_ball(position);
    return scoring_team;
}

void MatchState::synchronize_ball(const travesim::Vector2D& position) {
    this->previous_ball_position = position;
    this->has_previous_ball_position = true;
}

bool MatchState::is_finished(double elapsed_seconds) const {
    return this->duration_seconds > 0.0 && elapsed_seconds >= this->duration_seconds;
}

uint32_t MatchState::goals_blue() const {
    return this->blue_score;
}

uint32_t MatchState::goals_yellow() const {
    return this->yellow_score;
}

}  // namespace travesim::webots_adapter
