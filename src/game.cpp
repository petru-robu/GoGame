#include "../inc/game.h"

Game::Game(): ctx(13, GameType::AI)
{
    unsigned int window_width = 1920;
    unsigned int window_height = 1080;

    window.create(sf::VideoMode({window_width, window_height}), "Go Game!");
    window.setFramerateLimit(60);

    options_menu = new OptionsMenu(window, ctx);
    main_menu = new MainMenu(window, ctx);
    selector_menu = new SelectorMenu(window, ctx);

    ai_game_window = nullptr;
    local_game_window = nullptr;

    menu = main_menu;
}

void Game::Init()
{
    ctx.setState(GameState::MAIN_MENU);
    ctx.setPrevState(GameState::OPTIONS);
}

void Game::changeState()
{   
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
        local_game_window = new LocalGameWindow(window, ctx);
        menu = local_game_window;
        ctx.setPrevState(ctx.getState());
    }
    else if(ctx.getState() == GameState::AI_GAMEPLAY &&
    ctx.getState() != ctx.getPrevState())
    {
        ai_game_window = new AIGameWindow(window, ctx);
        menu = ai_game_window;
        ctx.setPrevState(ctx.getState());
    } 
}

void Game::Run()
{
    Init();
    
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