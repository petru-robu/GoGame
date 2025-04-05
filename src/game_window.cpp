#include "../inc/game_window.h"

GameWindow::GameWindow(sf::RenderWindow &window, GameContext &ctx):
IMenu(window, ctx),
turn(CellType::BLACK),
title(window, "Game of Go", 35.f, sf::Color::White, "./fonts/shuriken.ttf", {220, 70}),
end_game_button(window, "End Game", 30.f, sf::Color::White, "./fonts/robot-crush.ttf", {220, 130}),
clear_board_button(window, "Clear Board", 30.f, sf::Color::White, "./fonts/robot-crush.ttf", {220, 190}),
back_to_menu(window, "Back to menu", 30.f, sf::Color::White, "./fonts/robot-crush.ttf", {220, 250}),
to_play(window, "Black to play", 25.f, sf::Color::White, "./fonts/shuriken.ttf", {220, 860}),
game_type_label(window, "Playing locally!", 25.f, sf::Color::White, "./fonts/shuriken.ttf", {220, 920})
{
    visual_board = new VisualBoard(window, ctx);
}

void GameWindow::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        float mx = mouseButtonPressed->position.x;
        float my = mouseButtonPressed->position.y;

        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            if(end_game_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::MAIN_MENU);

                delete visual_board;
                visual_board = new VisualBoard(window, ctx);
            }

            if(clear_board_button.getBounds().contains({mx, my}))
            {
                delete visual_board;
                visual_board = new VisualBoard(window, ctx);
            }

            if(back_to_menu.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::MAIN_MENU);
            }

            visual_board->manageMouseClick({(int)mx, (int)my}, turn);

            if(turn == CellType::BLACK)
            {
                to_play.setString("BLACK to play");
            }
            else if(turn == CellType::WHITE)
            {
                to_play.setString("WHITE to play");
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

void GameWindow::Render()
{
    window.clear();

    title.Render(); 
    back_to_menu.Render();
    end_game_button.Render();
    clear_board_button.Render();
    to_play.Render();
    game_type_label.Render();

    visual_board->Render();

    
    window.display();
}

void GameWindow::Process()
{
    visual_board->process();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    end_game_button.colorOnHover(mouse_pos, sf::Color::Blue);
    clear_board_button.colorOnHover(mouse_pos, sf::Color::Blue);
    back_to_menu.colorOnHover(mouse_pos, sf::Color::Blue);

    visual_board->manageHovers(mouse_pos);
}

GameWindow::~GameWindow()
{
    delete visual_board;
}