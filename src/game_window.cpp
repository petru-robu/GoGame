#include "../inc/game_window.h"

GameWindow::GameWindow(sf::RenderWindow &window, GameContext &ctx):
IMenu(window, ctx),
visual_board(window, ctx)
{
    float wx = window.getSize().x;
    float wy = window.getSize().y;
}

void GameWindow::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        float mx = mouseButtonPressed->position.x;
        float my = mouseButtonPressed->position.y;

        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            visual_board.manageMouseClick({mx, my}, 0);
        }

        if (mouseButtonPressed->button == sf::Mouse::Button::Right)
        {
            visual_board.manageMouseClick({mx, my}, 1);
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

void GameWindow::Render()
{
    window.clear();
    visual_board.Render();
    window.display();
}

void GameWindow::Process()
{
    visual_board.process();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    visual_board.manageHovers(mouse_pos);
}