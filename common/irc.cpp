#include <irc.hpp>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <irc_numberic_replies.hpp>

irc::command irc::parseClientCommand(std::string clientCommand) {

    irc::command parsedCommand;
    parsedCommand.raw = clientCommand;

    size_t command_end = clientCommand.find_first_of(' ');
    if(command_end == std::string::npos) {
        //FIXME handle error reading client command
        std::cout << "Failed to parse command [" << clientCommand << "]" << std::endl;
    }

    parsedCommand.command = clientCommand.substr(0, command_end);

    size_t after_name = command_end + 1;
    std::string argsString = clientCommand.substr(after_name);
    size_t endOfSpaceSeperated = argsString.find_first_of(':');

    std::string last_args;
    if (endOfSpaceSeperated != std::string::npos) {
        last_args = argsString.substr(endOfSpaceSeperated + 1);
        argsString = argsString.substr(0, endOfSpaceSeperated);
    }

    std::istringstream iss(argsString);
    std::string arg;
    while (iss >> arg) {
        parsedCommand.arguments.push_back(arg);
    }



    if(!last_args.empty()) {
        parsedCommand.arguments.push_back(last_args);
    }

    return parsedCommand;
}

irc::command irc::parseCommand(const std::string& message) {
    command parsedCommand;
    parsedCommand.raw = message;
    size_t name_end = message.find_first_of(' ');

    if (name_end == std::string::npos) {
        return parsedCommand; 
    }
    parsedCommand.command = message.substr(0, name_end);
    // std::cout << "[\n" << parsedCommand.name << std::endl;

    size_t after_name = name_end + 1;
    std::string argsString = message.substr(after_name);
    size_t endOfSpaceSeperated = argsString.find_first_of(':');

    std::string last_args;
    if (endOfSpaceSeperated != std::string::npos) {
        last_args = argsString.substr(endOfSpaceSeperated + 1);
        argsString = argsString.substr(0, endOfSpaceSeperated);
    }

    std::istringstream iss(argsString);
    std::string arg;
    while (iss >> arg) {
        parsedCommand.arguments.push_back(arg);
    }



    if(!last_args.empty()) {
        parsedCommand.arguments.push_back(last_args);
    }

    // std::cout << "Arguments: " << std::endl;
    // for (const std::string& arg : parsedCommand.arguments) {
    //     std::cout << arg << std::endl;
    // }
    
    // std::cout << "]" << std::endl;
    return parsedCommand;
}

bool irc::isKnownNumericReply(const std::string& number) {
    if(number.length() != 3)
        return false;

    if(!std::all_of(number.begin(), number.end(), isdigit))
        return false;

    int n = std::stoi(number);

    if(validNumericReplies.find((irc::numeric_reply)n) != validNumericReplies.end())
        return true;

    return false;
}