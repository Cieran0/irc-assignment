#pragma once

#include <vector>
#include <string>

namespace irc
{
    struct command
    {
        std::string raw;
        std::string command;
        std::vector<std::string> arguments;
    };

    irc::command parseClientCommand(std::string clientCommand);
    
    irc::command parseCommand(const std::string& message);
    
    bool isKnownNumericReply(const std::string& message);

} // namespace irc
