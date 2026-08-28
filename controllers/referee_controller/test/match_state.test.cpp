#include <cassert>

#include "travesim_webots/match_state.hpp"

int main() {
    using travesim::Vector2D;
    using travesim::webots_adapter::MatchState;
    using travesim::webots_adapter::ScoringTeam;

    MatchState match(10.0);
    assert(match.observe_ball(Vector2D(0.0, 0.0)) == ScoringTeam::NONE);
    assert(match.observe_ball(Vector2D(0.8, 0.0)) == ScoringTeam::BLUE);
    assert(match.goals_blue() == 1);

    match.synchronize_ball(Vector2D(0.0, 0.0));
    assert(match.observe_ball(Vector2D(-0.8, 0.0)) == ScoringTeam::YELLOW);
    assert(match.goals_yellow() == 1);

    match.synchronize_ball(Vector2D(0.0, 0.3));
    assert(match.observe_ball(Vector2D(0.8, 0.3)) == ScoringTeam::NONE);
    assert(match.goals_blue() == 1);

    match.synchronize_ball(Vector2D(0.7, 0.25));
    assert(match.observe_ball(Vector2D(0.8, 0.15)) == ScoringTeam::BLUE);
    assert(match.goals_blue() == 2);

    match.synchronize_ball(Vector2D(0.8, 0.0));
    assert(match.observe_ball(Vector2D(0.7, 0.0)) == ScoringTeam::NONE);
    assert(match.goals_blue() == 2);

    assert(!match.is_finished(9.999));
    assert(match.is_finished(10.0));

    MatchState unlimited(0.0);
    assert(!unlimited.is_finished(100000.0));
    return 0;
}
