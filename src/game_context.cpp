#include "../inc/game_context.h"

GameContext::GameContext()
{}

GameContext& GameContext::getInstance()
{
    static GameContext instance;
    return instance;
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

void GameContext::setEnableSounds(bool es)
{
    sounds_enabled = es;
}
void GameContext::setEnableMusic(bool em)
{
    music_enabled = em;
}
void GameContext::setEnableLiberties(bool el)
{
    liberties_enabled = el;
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

bool GameContext::getSoundsEnabled() const
{
    return sounds_enabled;
}
bool GameContext::getMusicEnabled() const
{
    return music_enabled;
}
bool GameContext::getLibertiesEnabled() const
{
    return liberties_enabled;
}