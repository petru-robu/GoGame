#ifndef GAME_EXCEPTIONS
#define GAME_EXCEPTIONS

#include <exception>
#include <string>

class GameException : public std::exception 
{
protected:
    std::string message;

public:
    explicit GameException(const std::string& msg);
    const char* what() const noexcept override;
};

class ResourceLoadException : public GameException
{
public:
    explicit ResourceLoadException(const std::string& resourceName);
};

class InvalidMoveException : public GameException 
{
public:
    explicit InvalidMoveException(const std::string& reason);
};


#endif