#include "../inc/game.h"

Game::Game()
{
    unsigned int window_width = 1920;
    unsigned int window_height = 1080;

    window.create(sf::VideoMode({window_width, window_height}), "Go Game!");
    window.setFramerateLimit(60);

    try
    {
        options_menu = dynamic_cast<OptionsMenu*>(MenuFactory::createMenu(window, GameState::OPTIONS));
        main_menu = dynamic_cast<MainMenu*>(MenuFactory::createMenu(window, GameState::MAIN_MENU));
        selector_menu = dynamic_cast<SelectorMenu*>(MenuFactory::createMenu(window, GameState::SELECTOR_MENU));

        ai_game_window = nullptr;
        local_game_window = nullptr;

        menu = main_menu;
    }
    catch (const ResourceLoadException& e)
    {
        std::cerr<<e.what()<<"\n";
    }
}

Game& Game::getInstance()
{   
    static Game instance;
    return instance;
}

void Game::Init()
{
    GameContext::getInstance().setState(GameState::MAIN_MENU);
    GameContext::getInstance().setPrevState(GameState::OPTIONS);

    GameContext::getInstance().setCurrentTheme(lightTheme);
}

void Game::changeState()
{   
    GameContext& ctx = GameContext::getInstance();
    
    if(ctx.getState() == GameState::MAIN_MENU && 
    ctx.getState()  != ctx.getPrevState())
    {   
        menu = main_menu;
        ctx.setPrevState(ctx.getState());
    }
    else if(ctx.getState() == GameState::OPTIONS && 
    ctx.getState()  != ctx.getPrevState())
    {
        menu = options_menu;
        ctx.setPrevState(ctx.getState());
    }
    else if(ctx.getState() == GameState::SELECTOR_MENU &&
    ctx.getState()  != ctx.getPrevState())
    {
        menu = selector_menu;
        ctx.setPrevState(ctx.getState());
    }
    else if(ctx.getState() == GameState::LOCAL_GAMEPLAY && 
    ctx.getState()  != ctx.getPrevState())
    {
        if(ctx.getGameRunningState() == false)
        {
            local_game_window = dynamic_cast<LocalGameWindow*>(MenuFactory::createMenu(window, GameState::LOCAL_GAMEPLAY));
            ctx.setGameRunningState(true);
        }

        menu = local_game_window;
        ctx.setPrevState(ctx.getState());
    }
    else if(ctx.getState() == GameState::AI_GAMEPLAY &&
    ctx.getState() != ctx.getPrevState())
    {
        if(ctx.getGameRunningState() == false)
        {
            ai_game_window = dynamic_cast<AIGameWindow*>(MenuFactory::createMenu(window, GameState::AI_GAMEPLAY));
            ctx.setGameRunningState(true);
        }
        menu = ai_game_window;
        ctx.setPrevState(ctx.getState());
    } 
}

void Game::Run()
{
    Init();

    if(GameContext::getInstance().getMusicEnabled())
    {
        AudioPlayer::getInstance().playMusic();
    }
    
    while(window.isOpen())
    {
        changeState();

        menu->Process();

        while (const std::optional event = window.pollEvent()) 
        {
            menu->EventHandler(event);
        }

        menu->Render();
    }
}

Game::~Game()
{
    if(ai_game_window != nullptr)
    {
        delete ai_game_window;
    }
    if(local_game_window != nullptr)
    {
        delete local_game_window;
    }
        
    delete selector_menu;
    delete options_menu;
    delete main_menu;
}