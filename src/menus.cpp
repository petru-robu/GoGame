#include "../inc/menus.h"

MainMenu::MainMenu(sf::RenderWindow &window, GameContext& ctx): 
IMenu(window, ctx),
title(window, "Game of go", 65.f, sf::Color::White, "fonts/shuriken.ttf", {0,0}),
play_button(window, "Play", 40.f, sf::Color::White, "fonts/robot-crush.ttf", {0, 0}),
options_button(window, "Options", 40.f, sf::Color::White, "fonts/robot-crush.ttf", {0, 0}),
exit_button(window, "Exit", 40.f, sf::Color::White, "fonts/robot-crush.ttf", {0, 0})
{
    float wx = window.getSize().x;
    float wy = window.getSize().y;

    title.setPosition({wx/2.f, wy/2.f-300});
    play_button.setPosition({wx/2.f, wy/2.f-200});
    options_button.setPosition({wx/2.f, wy/2.f-100});
    exit_button.setPosition({wx/2.f, wy/2.f});
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
                ctx.setState(GameState::GAMEPLAY);
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
    title.Render();
    play_button.Render();
    options_button.Render();
    exit_button.Render();
    window.display();
}

void MainMenu::Process()
{   
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    play_button.colorOnHover(mouse_pos, sf::Color::Blue);
    options_button.colorOnHover(mouse_pos, sf::Color::Blue);
    exit_button.colorOnHover(mouse_pos, sf::Color::Blue);
}


OptionsMenu::OptionsMenu(sf::RenderWindow &window, GameContext& ctx):
IMenu(window, ctx),
back_button(window, "Back", 40.f, sf::Color::White, "fonts/robot-crush.ttf", {0,0})
{
    float wx = window.getSize().x;
    float wy = window.getSize().y;
    back_button.setPosition({wx/2, wy/2});
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
    back_button.Render();
    window.display();
}

void OptionsMenu::Process()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    back_button.colorOnHover(mouse_pos, sf::Color::Blue);
}