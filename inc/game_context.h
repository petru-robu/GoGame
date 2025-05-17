#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H
#include <SFML/Graphics.hpp>

#include "theme.h"

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
    GameState state = GameState::MAIN_MENU;
    GameState prev_state = GameState::UNDEFINED;
    GameState last_state = GameState::UNDEFINED;

    int game_size = 13;
    GameType game_type = GameType::LOCAL;

    bool game_running = false;
    bool sounds_enabled = true;
    bool music_enabled = true;
    bool liberties_enabled = false;

    Theme curr_theme;
    Theme last_theme;

    GameContext();
    GameContext(const GameContext&) = delete;
    void operator=(const GameContext&) = delete;
    
public:
    static GameContext& getInstance();

    void setState(GameState ns);
    void setPrevState(GameState ps);
    void setGameSize(int gs);
    void setGameType(GameType gt);
    void setGameRunningState(bool gr);

    void setCurrentTheme(const Theme& th);
    void setLastTheme(const Theme& th);

    void setEnableSounds(bool es);
    void setEnableMusic(bool em);
    void setEnableLiberties(bool el);

    GameState getState() const;
    GameState getPrevState() const;
    GameState getLastState() const;
    int getGameSize() const;
    bool getGameRunningState() const;

    Theme getCurrentTheme() const;
    Theme getLastTheme() const;

    bool getSoundsEnabled() const;
    bool getMusicEnabled() const;
    bool getLibertiesEnabled() const;
};

#endif