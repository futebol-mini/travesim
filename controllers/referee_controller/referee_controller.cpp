/**
 * @file referee_controller.cpp
 *
 * @author Felipe Gomes de Melo <felipegmelo.42@gmail.com>
 *
 * @brief
 *
 * @date 07/2025
 *
 * @copyright MIT License - Copyright (c) 2025 Futebol Mini
 */

#include <array>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <queue>
#include <vector>
#include <webots/Robot.hpp>
#include <webots/Supervisor.hpp>
#include <webots/Node.hpp>
#include <webots/Emitter.hpp>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <string>
#include <functional>

#include "travesim_adapters/data/data_common.hpp"
#include "travesim_webots/robot.hpp"
#include "travesim_webots/match_state.hpp"

#include "travesim_webots/message.hpp"

#include "travesim_adapters/protobuf/replacer_receiver.hpp"
#include "travesim_adapters/protobuf/team_receiver.hpp"
#include "travesim_adapters/protobuf/vision_sender.hpp"
#include "travesim_adapters/data/field_state.hpp"

#define DEFAULT_Z_M 0.002 // 2mm

inline std::shared_ptr<std::unordered_map<std::string, webots::Node*>> get_robots_references(webots::Field* children) {
    auto entities = std::make_shared<std::unordered_map<std::string, webots::Node*>>();
    auto count = children->getCount();

    for (int i = 0; i < count; i++) {
        webots::Node* node = children->getMFNode(i);
        auto* name = node->getField("name");

        if (name) {
            (*entities)[name->getSFString()] = node;
        }
    }

    return entities;
}

inline void convert_to_entity_state(travesim::EntityState& output, travesim::webots_adapter::Robot& input) {
    output.position = input.get_position2d();
    output.angular_position = input.get_yaw();
    output.velocity = input.get_linear_velocity();
    output.angular_velocity = input.get_angular_velocity();
}

inline std::string build_name_from_team_number(bool is_yellow, uint8_t number) {
    return std::string(is_yellow ? "Yellow" : "Blue") + std::string("Robot") + std::to_string(number);
}

struct InitialPose {
    std::array<double, 3> position;
    double yaw;
};

inline InitialPose capture_pose(travesim::webots_adapter::Robot& entity) {
    return InitialPose{ entity.get_position(), entity.get_yaw() };
}

inline void restore_pose(travesim::webots_adapter::Robot& entity, const InitialPose& pose) {
    entity.set_position(pose.position[0], pose.position[1], pose.position[2]);
    entity.set_yaw(pose.yaw);
    entity.stop();
}

inline void write_entity_json(std::ostream& output, const travesim::EntityState& entity) {
    output << "{\"x\":" << entity.position.x
           << ",\"y\":" << entity.position.y
           << ",\"vx\":" << entity.velocity.x
           << ",\"vy\":" << entity.velocity.y
           << ",\"orientation\":" << entity.angular_position
           << ",\"angular_velocity\":" << entity.angular_velocity << "}";
}

inline void write_team_json(std::ostream& output, const std::vector<travesim::EntityState>& team) {
    output << "[";
    for (size_t i = 0; i < team.size(); i++) {
        if (i > 0) {
            output << ",";
        }
        write_entity_json(output, team[i]);
    }
    output << "]";
}

inline void write_frame_json(
    std::ostream& output,
    double elapsed_seconds,
    const travesim::FieldState& field_state,
    travesim::webots_adapter::ScoringTeam scoring_team,
    bool finished) {
    output << std::setprecision(10)
           << "{\"type\":\"frame\",\"time\":" << elapsed_seconds
           << ",\"step\":" << field_state.time_step
           << ",\"goals_blue\":" << field_state.goals_blue
           << ",\"goals_yellow\":" << field_state.goals_yellow
           << ",\"goal\":\"";

    if (scoring_team == travesim::webots_adapter::ScoringTeam::BLUE) {
        output << "blue";
    } else if (scoring_team == travesim::webots_adapter::ScoringTeam::YELLOW) {
        output << "yellow";
    }

    output << "\",\"finished\":" << (finished ? "true" : "false") << ",\"ball\":";
    write_entity_json(output, field_state.ball);
    output << ",\"yellow\":";
    write_team_json(output, field_state.yellow_team);
    output << ",\"blue\":";
    write_team_json(output, field_state.blue_team);
    output << "}\n";
    output.flush();
}

int main(int argc, char** argv) {
    /**
     * External interfaces definitions
     */

    const size_t robots_per_team = std::stoi(argv[1]);

    std::string referee_address_str(argv[2]);
    uint32_t referee_port = std::stoi(argv[3]);

    std::string yellow_address_str(argv[4]);
    uint32_t yellow_port = std::stoi(argv[5]);

    std::string blue_address_str(argv[6]);
    uint32_t blue_port = std::stoi(argv[7]);

    std::string multicast_addr_str(argv[8]);
    uint32_t multicast_port = std::stoi(argv[9]);

    const double match_duration = argc > 10 ? std::stod(argv[10]) : 600.0;
    const std::string telemetry_path = argc > 11 ? argv[11] : "";

    bool specific_source = false;
    const travesim::TeamsFormation teams_formation = std::invoke([robots_per_team] {
        switch (robots_per_team) {
            case 3:
                return travesim::THREE_ROBOTS_PER_TEAM;

            case 5:
                return travesim::FIVE_ROBOTS_PER_TEAM;

            default:
                std::cout << "Invalid robots_per_team value! Got " << robots_per_team << " should be 3 or 5" << std::endl;
                std::exit(-1);
        }
    });

    std::cout << "Referee addr: " << referee_address_str << std::endl;
    std::cout << "Referee port: " << referee_port << std::endl;

    std::cout << "Yellow addr: " << yellow_address_str << std::endl;
    std::cout << "Yellow port: " << yellow_port << std::endl;

    std::cout << "Blue addr: " << blue_address_str << std::endl;
    std::cout << "Blue port: " << blue_port << std::endl;

    std::cout << "Vision addr: " << multicast_addr_str << std::endl;
    std::cout << "Vision port: " << multicast_port << std::endl;
    std::cout << "Match duration: " << match_duration << " s" << std::endl;
    if (!telemetry_path.empty()) {
        std::cout << "Telemetry path: " << telemetry_path << std::endl;
    }

    travesim::proto::VisionSender vision_sender(multicast_addr_str, multicast_port);
    travesim::FieldState field_state(teams_formation);
    travesim::webots_adapter::MatchState match_state(match_duration);

    std::ofstream telemetry;
    if (!telemetry_path.empty()) {
        telemetry.open(telemetry_path, std::ios::out | std::ios::trunc);
        if (!telemetry.is_open()) {
            std::cerr << "Could not open telemetry file: " << telemetry_path << std::endl;
            return -1;
        }
    }

    travesim::proto::TeamReceiver yellow_receiver(yellow_address_str, yellow_port, true, specific_source, teams_formation);

    travesim::TeamCommand yellow_command(teams_formation);

    travesim::proto::TeamReceiver blue_receiver(blue_address_str, blue_port, false, specific_source, teams_formation);

    travesim::TeamCommand blue_command(teams_formation);

    travesim::proto::ReplacerReceiver referee_receiver(referee_address_str, referee_port, specific_source);
    std::queue<std::shared_ptr<travesim::EntityState>> states_queue;

    /**
     * Webots interfaces definitions
     */

    auto referee = std::make_unique<webots::Supervisor>();

    auto time_step = (uint16_t) referee->getBasicTimeStep();

    webots::Field* children = referee->getRoot()->getField("children");

    auto robots = get_robots_references(children);

    webots::Emitter* yellow_team_emitter = referee->getEmitter("yellow_team");
    webots::Emitter* blue_team_emitter = referee->getEmitter("blue_team");

    yellow_team_emitter->setChannel(0);
    blue_team_emitter->setChannel(1);

    /**
     * Loop preparation
     */

    uint32_t frame = 0;

    std::vector<travesim::webots_adapter::Robot> yellow_robots;
    yellow_robots.reserve(robots_per_team);

    std::vector<travesim::webots_adapter::Robot> blue_robots;
    blue_robots.reserve(robots_per_team);

    travesim::webots_adapter::Robot ball((*robots)["VssBall"]);

    for (size_t i = 0; i < robots_per_team; i++) {
        std::string yellow_robot_name = "YellowRobot" + std::to_string(i);
        std::string blue_robot_name = "BlueRobot" + std::to_string(i);

        yellow_robots.emplace_back((*robots)[yellow_robot_name]);
        blue_robots.emplace_back((*robots)[blue_robot_name]);
    }

    const InitialPose initial_ball_pose = capture_pose(ball);
    std::vector<InitialPose> initial_yellow_poses;
    std::vector<InitialPose> initial_blue_poses;
    initial_yellow_poses.reserve(robots_per_team);
    initial_blue_poses.reserve(robots_per_team);

    for (size_t i = 0; i < robots_per_team; i++) {
        initial_yellow_poses.push_back(capture_pose(yellow_robots[i]));
        initial_blue_poses.push_back(capture_pose(blue_robots[i]));
    }

    match_state.synchronize_ball(ball.get_position2d());
    const double match_start_time = referee->getTime();

    while (referee->step(time_step) != -1) {
        /**
         * Process messages from referee
         */

        bool received_new_msg = referee_receiver.receive(&states_queue);

        if (received_new_msg) {
            referee->simulationSetMode(webots::Supervisor::SIMULATION_MODE_PAUSE);

            while (!states_queue.empty()) {
                if (std::dynamic_pointer_cast<travesim::RobotState>(states_queue.front()) != nullptr) {
                    // Incoming state is a robot state
                    auto state = std::dynamic_pointer_cast<travesim::RobotState>(states_queue.front());

                    auto& team_array = (state->is_yellow ? yellow_robots : blue_robots);

                    team_array[state->id].set_position(state->position.x, state->position.y, DEFAULT_Z_M);
                    team_array[state->id].set_yaw(state->angular_position);
                    team_array[state->id].stop();
                } else {
                    // Incoming state is an entity state (ball)
                    auto state = std::dynamic_pointer_cast<travesim::EntityState>(states_queue.front());

                    ball.set_position(state->position.x, state->position.y, DEFAULT_Z_M);
                    ball.set_yaw(state->angular_position);
                    ball.stop();
                }

                states_queue.pop();
            }

            match_state.synchronize_ball(ball.get_position2d());

            referee->simulationSetMode(webots::Supervisor::SIMULATION_MODE_REAL_TIME);
        }

        /**
         * Send world info to teams
         */

        // FIXME: Use std::chronos
        // Time comes in seconds, but time_step is in milliseconds
        field_state.time_step = (uint16_t) (referee->getTime() * 1e3 / time_step);

        for (size_t i = 0; i < robots_per_team; i++) {
            convert_to_entity_state(field_state.yellow_team[i], yellow_robots[i]);
            convert_to_entity_state(field_state.blue_team[i], blue_robots[i]);
        }

        convert_to_entity_state(field_state.ball, ball);

        const auto scoring_team = match_state.observe_ball(field_state.ball.position);
        field_state.goals_blue = match_state.goals_blue();
        field_state.goals_yellow = match_state.goals_yellow();

        const double elapsed_seconds = referee->getTime() - match_start_time;
        const bool match_finished = match_state.is_finished(elapsed_seconds);

        vision_sender.send(&field_state);

        if (telemetry.is_open()) {
            write_frame_json(telemetry, elapsed_seconds, field_state, scoring_team, match_finished);
        }

        if (scoring_team != travesim::webots_adapter::ScoringTeam::NONE) {
            referee->simulationSetMode(webots::Supervisor::SIMULATION_MODE_PAUSE);
            restore_pose(ball, initial_ball_pose);
            for (size_t i = 0; i < robots_per_team; i++) {
                restore_pose(yellow_robots[i], initial_yellow_poses[i]);
                restore_pose(blue_robots[i], initial_blue_poses[i]);
            }
            match_state.synchronize_ball(ball.get_position2d());
            referee->simulationSetMode(webots::Supervisor::SIMULATION_MODE_REAL_TIME);
        }

        if (match_finished) {
            std::cout << "Match finished: blue " << match_state.goals_blue()
                      << " x " << match_state.goals_yellow() << " yellow" << std::endl;
            referee->simulationQuit(0);
            break;
        }

        /**
         * Wait for teams to send a command
         */

        yellow_receiver.receive(&yellow_command);
        blue_receiver.receive(&blue_command);

        /**
         * Relay command to robots
         */

        frame++;

        travesim::webots_adapter::message_t<MAX_ROBOTS> yellow_message;
        travesim::webots_adapter::message_t<MAX_ROBOTS> blue_message;

        yellow_message.frame = frame;
        blue_message.frame = frame;

        for (size_t i = 0; i < robots_per_team; i++) {
            yellow_message.left_speed[i] = yellow_command.robot_command[i].left_speed;
            yellow_message.right_speed[i] = yellow_command.robot_command[i].right_speed;

            blue_message.left_speed[i] = blue_command.robot_command[i].left_speed;
            blue_message.right_speed[i] = blue_command.robot_command[i].right_speed;
        }

        yellow_team_emitter->send(&yellow_message, sizeof(yellow_message));
        blue_team_emitter->send(&blue_message, sizeof(blue_message));
    }

    return 0;
}
