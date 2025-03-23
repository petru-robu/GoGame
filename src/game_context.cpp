#include "../inc/game_context.h"

GameContext::GameContext(int gs): game_size(gs)
{
    state = GameState::MAIN_MENU;
    prev_state = GameState::UNDEFINED;
}

//setters
void GameContext::setState(GameState ns)
{
    state = ns;
}
void GameContext::setPrevState(GameState ps)
{
    prev_state = ps;
}

//getters
GameState GameContext::getState()
{
    return state;
}
GameState GameContext::getPrevState()
{
    return prev_state;
}
int GameContext::getGameSize()
{
    return game_size;
}