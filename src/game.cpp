#include "../inc/game.h"

Game::Game(): ctx(13)
{
    int window_width = 1920;
    int window_height = 1080;
    window.create(sf::VideoMode({window_width, window_height}), "Go Game!");
    window.setFramerateLimit(60);

    options_menu = new OptionsMenu(window, ctx);
    main_menu = new MainMenu(window, ctx);
    game_window = new GameWindow(window, ctx);

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
    else if(ctx.getState() == GameState::GAMEPLAY && 
    ctx.getState()  != ctx.getPrevState())
    {
        menu = game_window;
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
    delete game_window;
    delete options_menu;
    delete main_menu;
}