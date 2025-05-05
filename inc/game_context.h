#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H
#include <SFML/Graphics.hpp>

enum class GameState 
{
    MAIN_MENU,
    SELECTOR_MENU,
    OPTIONS,
    LOCAL_GAMEPLAY,
    AI_GAMEPLAY,
    UNDEFINED
};

enum class GameType
{
    LOCAL,
    AI
};

class GameContext
{
private:
    GameState state;
    GameState prev_state;
    GameState last_state;

    int game_size;
    GameType game_type;

    bool game_running;
    
public:
    explicit GameContext(int gs, GameType gt);

    void setState(GameState ns);
    void setPrevState(GameState ps);
    void setGameSize(int gs);
    void setGameType(GameType gt);
    void setGameRunningState(bool gr);

    GameState getState() const;
    GameState getPrevState() const;
    GameState getLastState() const;
    int getGameSize() const;
    bool getGameRunningState() const;
};

#endif