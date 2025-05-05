#include "../inc/game_context.h"

GameContext::GameContext(int gs, GameType gt): game_size(gs), game_type(gt)
{
    state = GameState::MAIN_MENU;
    prev_state = GameState::UNDEFINED;
    game_running = false;
}

//setters
void GameContext::setState(GameState ns)
{
    last_state = state;
    state = ns;
}
void GameContext::setPrevState(GameState ps)
{
    prev_state = ps;
}
void GameContext::setGameSize(int gs)
{
    game_size = gs;
}
void GameContext::setGameType(GameType gt)
{
    game_type = gt;
}
void GameContext::setGameRunningState(bool gr)
{
    game_running = gr;
}

//getters
GameState GameContext::getState() const
{
    return state;
}
GameState GameContext::getPrevState() const
{
    return prev_state;
}
int GameContext::getGameSize() const
{
    return game_size;
}
GameState GameContext::getLastState() const
{
    return last_state;
}
bool GameContext::getGameRunningState() const
{
    return game_running;
}