#include "../inc/game_exceptions.h"

GameException::GameException(const std::string& msg): message(msg)
{}

const char* GameException::what() const noexcept 
{
    return message.c_str();
}

ResourceLoadException::ResourceLoadException(const std::string& resourceName):
GameException("Failed to load resource: " + resourceName)
{}

InvalidMoveException::InvalidMoveException(const std::string& reason):
GameException("Invalid move: " + reason) 
{}