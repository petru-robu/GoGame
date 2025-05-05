#include "../inc/game_window.h"

LocalGameWindow::LocalGameWindow(sf::RenderWindow &window):
IMenu(window),
turn(CellType::BLACK),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    visual_board = new VisualBoard(window);

    title = new Label(window, "Game of Go", 35.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {220, 70});
    end_game_button = new Button(window, "End Game", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 130});
    clear_board_button = new Button(window, "Clear Board", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 190});
    options_menu_button = new Button(window, "Options", 30.f, Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 250});
    to_play = new Label(window, "Black to play", 30.f,  Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {1700, 130});
    game_type_label = new Label(window, "Playing locally!", 30.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {1700, 70});

    pass_button = new Button(window, "pass move", 40.f, Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {1700, 900}, true);

    ui_elements.push_back(title);
    ui_elements.push_back(end_game_button);
    ui_elements.push_back(clear_board_button);
    ui_elements.push_back(options_menu_button);
    ui_elements.push_back(to_play);
    ui_elements.push_back(game_type_label);
    ui_elements.push_back(pass_button);

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void LocalGameWindow::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            GameContext::getInstance().setState(GameState::MAIN_MENU);
            GameContext::getInstance().setGameRunningState(false);
        }
    }

    if (event->is<sf::Event::Closed>())
        window.close();

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
        {
            btn->HandleClick(event);
        }      
    }

    if(end_game_button->WasClicked())
    {
        GameContext::getInstance().setState(GameState::MAIN_MENU);
        GameContext::getInstance().setGameRunningState(false);
    }

    if(clear_board_button->WasClicked())
    {
        delete visual_board;
        visual_board = new VisualBoard(window);
    }

    if(options_menu_button->WasClicked())
    {
        GameContext::getInstance().setState(GameState::OPTIONS);
    }

    if(pass_button->WasClicked())
    {
        if(turn == CellType::WHITE)
        {
            turn = CellType::BLACK;
        }  
        else
        {
            turn = CellType::WHITE;
        }       
    }

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->ResetClick();
    }

    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;

            visual_board->manageMouseClick({(int)mx, (int)my}, turn);

            if(turn == CellType::BLACK)
            {
                to_play->setString("BLACK to play");
            }
            else if(turn == CellType::WHITE)
            {
                to_play->setString("WHITE to play");
            }
        }
    }
}

void LocalGameWindow::Render()
{
    window.clear();

    window.draw(backgroundSprite);
    
    for(IDrawable* el:ui_elements)
    {
        el->Render();
    }

    visual_board->Render();
    window.display();
}

void LocalGameWindow::Process()
{
    visual_board->process();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    end_game_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    clear_board_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    options_menu_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    pass_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);

    visual_board->manageHovers(mouse_pos);
}

LocalGameWindow::~LocalGameWindow()
{
    delete visual_board;
}

AIGameWindow::AIGameWindow(sf::RenderWindow &window):
IMenu(window),
turn(CellType::BLACK),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    visual_board = new VisualBoard(window);

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);

    title = new Label(window, "AI is work in progress!\n\nPlease come back when it's ready.\n\nMeanwhile, you can play locally.", 35.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {700, 350});
    end_game_button = new Button(window, "End Game", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 130});
    clear_board_button = new Button(window, "Clear Board", 30.f,  Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 190});
    options_menu_button = new Button(window, "Options", 30.f, Colors::BUTTON_COLOR, "./fonts/robot-crush.ttf", {220, 250});
    game_type_label = new Label(window, "Playing against AI!", 30.f, Colors::TITLE_COLOR, "./fonts/shuriken.ttf", {1700, 70});

    ui_elements.push_back(title);
    ui_elements.push_back(end_game_button);
    ui_elements.push_back(clear_board_button);
    ui_elements.push_back(game_type_label);
    ui_elements.push_back(options_menu_button);
}

void AIGameWindow::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            GameContext::getInstance().setState(GameState::MAIN_MENU);
            GameContext::getInstance().setGameRunningState(false);
        }
    }

    if (event->is<sf::Event::Closed>())
        window.close();

    if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
    {
        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
        {
            float mx = mouseButtonPressed->position.x;
            float my = mouseButtonPressed->position.y;

            visual_board->manageMouseClick({(int)mx, (int)my}, turn);
        }
    }

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
        {
            btn->HandleClick(event);
        }      
    }

    if(end_game_button->WasClicked())
    {
        GameContext::getInstance().setState(GameState::MAIN_MENU);
        GameContext::getInstance().setGameRunningState(false);
    }

    if(clear_board_button->WasClicked())
    {
        delete visual_board;
        visual_board = new VisualBoard(window);
    }

    if(options_menu_button->WasClicked())
    {
        GameContext::getInstance().setState(GameState::OPTIONS);
    }

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->ResetClick();
    }
}   

void AIGameWindow::Render()
{
    window.clear();

    window.draw(backgroundSprite);

    
    title->Render();
    window.display();
}

void AIGameWindow::Process()
{
    visual_board->process();

    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    end_game_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    clear_board_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);

    visual_board->manageHovers(mouse_pos);
}

AIGameWindow::~AIGameWindow()
{
    delete visual_board;
}