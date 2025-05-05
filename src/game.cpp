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
        if(ctx.getGameRunningState() == false)
        {
            local_game_window = new LocalGameWindow(window, ctx);
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
            ai_game_window = new AIGameWindow(window, ctx);
            ctx.setGameRunningState(true);
        }
        menu = ai_game_window;
        ctx.setPrevState(ctx.getState());
    } 
}

void Game::Run()
{
    Init();
    std::vector<sf::Sound> activeSounds;
    
    while(window.isOpen())
    {
        changeState();

        menu->Process();

        while (const std::optional event = window.pollEvent()) 
        {
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Space)
                {
                    // Load the sound buffer
                    sf::SoundBuffer buff;
                    if (buff.loadFromFile("audio/ou.wav"))
                    {
                        sf::Sound sound(buff);
                        sound.setVolume(100);  // Optional, set volume here if necessary
                        sound.play();
                        
                        // Store the sound in the activeSounds vector to keep it alive
                        activeSounds.push_back(std::move(sound));  
                    }
                    else
                    {
                        std::cerr << "Failed to load sound file!" << std::endl;
                    }
                }
            }

            menu->EventHandler(event);
        }

        for (auto it = activeSounds.begin(); it != activeSounds.end(); )
        {
            if (it->getStatus() == sf::SoundSource::Status::Stopped)
            {
                // Remove stopped sounds from the vector
                it = activeSounds.erase(it);
            }
            else
            {
                ++it;
            }
        }
        //audio_player.update();
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