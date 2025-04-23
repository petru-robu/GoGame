#include "../inc/game_window.h"

LocalGameWindow::LocalGameWindow(sf::RenderWindow &window, GameContext &ctx):
IMenu(window, ctx),
turn(CellType::BLACK),
title(window, "Game of Go", 35.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {220, 70}),
end_game_button(window, "End Game", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 130}),
clear_board_button(window, "Clear Board", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 190}),
to_play(window, "Black to play", 30.f,  Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {1700, 130}),
game_type_label(window, "Playing locally!", 30.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {1700, 70}),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    visual_board = new VisualBoard(window, ctx);

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void LocalGameWindow::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;
            if(end_game_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::MAIN_MENU);
            }

            if(clear_board_button.getBounds().contains({mx, my}))
            {
                delete visual_board;
                visual_board = new VisualBoard(window, ctx);
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

void LocalGameWindow::Render()
{
    window.clear();

    window.draw(backgroundSprite);
    title.Render(); 

    end_game_button.Render();
    clear_board_button.Render();
    to_play.Render();
    game_type_label.Render();

    visual_board->Render();
    window.display();
}

void LocalGameWindow::Process()
{
    visual_board->process();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    end_game_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    clear_board_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);

    visual_board->manageHovers(mouse_pos);
}

LocalGameWindow::~LocalGameWindow()
{
    delete visual_board;
}


AIGameWindow::AIGameWindow(sf::RenderWindow &window, GameContext &ctx):
IMenu(window, ctx),
turn(CellType::BLACK),
title(window, "Game of Go", 35.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {220, 70}),
end_game_button(window, "End Game", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 130}),
clear_board_button(window, "Clear Board", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 190}),
game_type_label(window, "Playing against AI!", 30.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {1700, 70}),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    visual_board = new VisualBoard(window, ctx);

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void AIGameWindow::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;
            if(end_game_button.getBounds().contains({mx, my}))
            {
                ctx.setState(GameState::MAIN_MENU);
            }

            if(clear_board_button.getBounds().contains({mx, my}))
            {
                delete visual_board;
                visual_board = new VisualBoard(window, ctx);
            }

            visual_board->manageMouseClick({(int)mx, (int)my}, turn);
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

void AIGameWindow::Render()
{
    window.clear();

    window.draw(backgroundSprite);
    title.Render(); 

    end_game_button.Render();
    clear_board_button.Render();
    game_type_label.Render();

    visual_board->Render();
    window.display();
}

void AIGameWindow::Process()
{
    visual_board->process();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    end_game_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    clear_board_button.colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);

    visual_board->manageHovers(mouse_pos);
}

AIGameWindow::~AIGameWindow()
{
    delete visual_board;
}