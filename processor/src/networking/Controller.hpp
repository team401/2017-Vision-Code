
//
// Created by cameronearle on 1/20/17.
//

#ifndef PROJECT_CONTROLLER_HPP
#define PROJECT_CONTROLLER_HPP


#include "../abstraction/Camera.hpp"
#include "../processing/GoalProc.hpp"
#include "../processing/GearProc.hpp"
#include "Streamer.hpp"

#include <map>

class Controller {
public:
    Controller(Configuration config_, Camera *goalCamera_, Camera *gearCamera_, Processor *goalProc_, Processor *gearProc_, Streamer *streamer_, int port_);
    void run();
    Configuration getCurrentSettings();
private:
    enum Command {
        INIT,
        PING,
        SETTINGS_GOAL_PROC_CAMERA,
        SETTINGS_GEAR_PROC_CAMERA,
        SETTINGS_GOAL_STREAM_CAMERA,
        SETTINGS_GEAR_STREAM_CAMERA,
        SETTINGS_GOAL_PROC,
        SETTINGS_GEAR_PROC,
        SETTINGS_STREAM_COMPRESSION,
        MODE_GOAL_PROC,
        MODE_GEAR_PROC,
        MODE_GOAL_STREAM,
        MODE_GEAR_STREAM,
        MODE_STREAMER_OFF,
        MODE_STREAMER_GOAL,
        MODE_STREAMER_GEAR,
        ACTION_WRITE_CONFIG,
        ACTION_RESET_CONFIG
    };

    std::map<std::string, Command> commandMapping = {
            std::make_pair("INIT", INIT),
            std::make_pair("PING", PING),
            std::make_pair("SETTINGS_GOAL_PROC_CAMERA", SETTINGS_GOAL_PROC_CAMERA),
            std::make_pair("SETTINGS_GEAR_PROC_CAMERA", SETTINGS_GEAR_PROC_CAMERA),
            std::make_pair("SETTINGS_GOAL_STREAM_CAMERA", SETTINGS_GOAL_STREAM_CAMERA),
            std::make_pair("SETTINGS_GEAR_STREAM_CAMERA", SETTINGS_GEAR_STREAM_CAMERA),
            std::make_pair("SETTINGS_GOAL_PROC", SETTINGS_GOAL_PROC),
            std::make_pair("SETTINGS_GEAR_PROC", SETTINGS_GEAR_PROC),
            std::make_pair("SETTINGS_STREAM_COMPRESSION", SETTINGS_STREAM_COMPRESSION),
            std::make_pair("MODE_GOAL_PROC", MODE_GOAL_PROC),
            std::make_pair("MODE_GEAR_PROC", MODE_GEAR_PROC),
            std::make_pair("MODE_GOAL_STREAM", MODE_GOAL_STREAM),
            std::make_pair("MODE_GEAR_STREAM", MODE_GEAR_STREAM),
            std::make_pair("MODE_STREAMER_OFF", MODE_STREAMER_OFF),
            std::make_pair("MODE_STREAMER_GOAL", MODE_STREAMER_GOAL),
            std::make_pair("MODE_STREAMER_GEAR", MODE_STREAMER_GEAR),
            std::make_pair("ACTION_WRITE_CONFIG", ACTION_WRITE_CONFIG),
            std::make_pair("ACTION_RESET_CONFIG", ACTION_RESET_CONFIG)
    };

    enum CameraMode {
        PROC,
        STREAM
    };

    struct ParsedCommand {
        Command command;
        std::map<std::string, std::string> args;
        bool valid = false;
    };

    Configuration config;
    Configuration storedSettings; //The current settings, updated every time we get new commands
    Configuration lastSettings;

    int port;
    Camera *goalCamera;
    Camera *gearCamera;
    Processor *goalProc;
    Processor *gearProc;
    Streamer *streamer;

    CameraMode goalCameraMode;
    CameraMode gearCameraMode;
    
    void setGoalCamera(CameraMode mode);
    void setGearCamera(CameraMode mode);

    ParsedCommand parseCommand(std::string input);
    void react(ParsedCommand command);
    void postAction(ParsedCommand command);


    std::string ld = "Controller";
};


#endif //PROJECT_CONTROLLER_HPP
