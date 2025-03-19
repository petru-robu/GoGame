#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H
#include <SFML/Graphics.hpp>

enum class GameState {
    MAIN_MENU,
    OPTIONS,
    GAMEPLAY
};

class GameContext
{
private:
    GameState state;
    GameState prev_state;
    int game_size;
    
public:
    GameContext(int gs);

    void setState(GameState ns);
    void setPrevState(GameState ps);
    void setGameSize(int game_size);

    GameState getState();
    GameState getPrevState();
    int getGameSize();
};

#endif