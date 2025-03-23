#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H
#include <SFML/Graphics.hpp>

enum class GameState {
    MAIN_MENU,
    OPTIONS,
    GAMEPLAY,
    UNDEFINED
};

class GameContext
{
private:
    GameState state;
    GameState prev_state;
    int game_size;
    
public:
    explicit GameContext(int gs);

    void setState(GameState ns);
    void setPrevState(GameState ps);

    GameState getState();
    GameState getPrevState();
    int getGameSize();
};

#endif