#include "../inc/menus.h"

MainMenu::MainMenu(sf::RenderWindow &window, GameContext& ctx): 
IMenu(window, ctx),
title(window, "Game of go", 65.f, Colors::TITLE_COLOR, "fonts/shuriken.ttf", {0,0}),
play_button(window, "Play", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0, 0}),
options_button(window, "Options", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0, 0}),
exit_button(window, "Exit", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0, 0}),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    float wx = window.getSize().x;
    float wy = window.getSize().y;

    title.setPosition({wx/2.f, wy/2.f-300});
    play_button.setPosition({wx/2.f, wy/2.f-200});
    options_button.setPosition({wx/2.f, wy/2.f-100});
    exit_button.setPosition({wx/2.f, wy/2.f});

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void MainMenu::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;

            if(exit_button.getBounds().contains({mx, my}))
                window.close();

            if(options_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::OPTIONS);
            }

            if(play_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::SELECTOR_MENU);
            }
        }
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            window.close();
    }

    if (event->is<sf::Event::Closed>())
        window.close();
}

void MainMenu::Render()
{
    window.clear();

    window.draw(backgroundSprite);

    title.Render();
    play_button.Render();
    options_button.Render();
    exit_button.Render();
    window.display();
}

void MainMenu::Process()
{   
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    play_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    options_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    exit_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
}


OptionsMenu::OptionsMenu(sf::RenderWindow &window, GameContext& ctx):
IMenu(window, ctx),
back_button(window, "Back", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    float wx = window.getSize().x;
    float wy = window.getSize().y;
    back_button.setPosition({wx/2, wy/2});

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void OptionsMenu::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;

            if(back_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::MAIN_MENU);
            }
        }
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            ctx.setState(GameState::MAIN_MENU);
        }
    }

    if (event->is<sf::Event::Closed>())
        window.close();
    
}

void OptionsMenu::Render()
{
    window.clear();
    window.draw(backgroundSprite);
    back_button.Render();
    window.display();
}

void OptionsMenu::Process()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    back_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
}

SelectorMenu::SelectorMenu(sf::RenderWindow &window, GameContext& ctx):
IMenu(window, ctx),
select_board_size(window, "select board size: ", 40.f, Colors::TITLE_COLOR, "fonts/shuriken.ttf", {0,0}),
select_game_type(window, "select game type: ", 40.f, Colors::TITLE_COLOR, "fonts/shuriken.ttf", {0,0}),
play_button(window, "Play", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}),
back_button(window, "Back", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}),
l_9x9(window, "9 by 9", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false),
l_13x13(window, "13 by 13", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, true),
l_19x19(window, "19 by 19", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false),
l_AI(window, "Play vs ai", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, true),
l_LOCAL(window, "Play Locally", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    curr_game_size = 13;
    curr_game_mode = GameType::AI;

    float mx = window.getSize().x/2;
    float my = window.getSize().y/2;

    select_board_size.setPosition({mx+10, my-400});
    select_game_type.setPosition({mx+10, my-100});
    play_button.setPosition({mx, my+200});
    back_button.setPosition({mx, my+300});

    l_9x9.setPosition({mx-250, my-300});
    l_13x13.setPosition({mx, my-300});
    l_19x19.setPosition({mx+250, my-300});

    l_AI.setPosition({mx-160, my});
    l_LOCAL.setPosition({mx+140, my});
    

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void SelectorMenu::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;

            if(back_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::MAIN_MENU);
            }

            if(play_button.getBounds().contains({mx, my}))
            {
                ctx.setGameSize(curr_game_size);
                ctx.setGameType(curr_game_mode);

                if(curr_game_mode == GameType::LOCAL)
                {
                    ctx.setState(GameState::LOCAL_GAMEPLAY);
                }
                else if(curr_game_mode == GameType::AI)
                {
                    ctx.setState(GameState::AI_GAMEPLAY);
                }
            }

            if(l_9x9.getBounds().contains({mx, my}))
            {
                l_13x13.setBorders(false);
                l_19x19.setBorders(false);

                l_9x9.setBorders(true);
                curr_game_size = 9;
            }

            if(l_13x13.getBounds().contains({mx, my}))
            {
                l_9x9.setBorders(false);
                l_19x19.setBorders(false);
                
                l_13x13.setBorders(true);
                curr_game_size = 13;
            }

            if(l_19x19.getBounds().contains({mx, my}))
            {
                l_9x9.setBorders(false);
                l_13x13.setBorders(false);
                
                l_19x19.setBorders(true);
                curr_game_size = 19;
            }

            if(l_AI.getBounds().contains({mx, my}))
            {
                l_LOCAL.setBorders(false);
                l_AI.setBorders(true);
                curr_game_mode = GameType::AI;
            }

            if(l_LOCAL.getBounds().contains({mx, my}))
            {
                l_AI.setBorders(false);
                l_LOCAL.setBorders(true);
                curr_game_mode = GameType::LOCAL;
            }
        }
    }

    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            ctx.setState(GameState::MAIN_MENU);
        }
    }

    if (event->is<sf::Event::Closed>())
        window.close(); 
}

void SelectorMenu::Render()
{
    window.clear();
    window.draw(backgroundSprite);

    select_board_size.Render();
    select_game_type.Render();
    play_button.Render();
    back_button.Render();

    l_9x9.Render();
    l_13x13.Render();
    l_19x19.Render();

    l_AI.Render();
    l_LOCAL.Render();

    window.display();
}

void SelectorMenu::Process()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    back_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    play_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
}