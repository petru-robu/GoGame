#include "../inc/menus.h"

MainMenu::MainMenu(sf::RenderWindow &window, GameContext& ctx): 
IMenu(window, ctx),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    title = new Label(window, "Game of go", 65.f, Colors::TITLE_COLOR, "fonts/shuriken.ttf", {0,0});
    play_button = new Button(window, "Play", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0, 0});
    options_button = new Button(window, "Options", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0, 0});
    exit_button = new Button(window, "Exit", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0, 0});

    ui_elements.push_back(title);
    ui_elements.push_back(play_button);
    ui_elements.push_back(options_button);
    ui_elements.push_back(exit_button);

    float wx = window.getSize().x;
    float wy = window.getSize().y;

    title->setPosition({wx/2.f, wy/2.f-300});
    play_button->setPosition({wx/2.f, wy/2.f-200});
    options_button->setPosition({wx/2.f, wy/2.f-100});
    exit_button->setPosition({wx/2.f, wy/2.f});

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void MainMenu::EventHandler(const std::optional<sf::Event> &event)
{
    if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
            window.close();
    }

    if (event->is<sf::Event::Closed>())
        window.close();


    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->HandleClick(event);
    }

    if(exit_button->WasClicked())
    {
        exit_button->ResetClick();
        window.close();
    }

    if(options_button->WasClicked())
    {
        options_button->ResetClick();
        ctx.setState(GameState::OPTIONS);
    }

    if(play_button->WasClicked())
    {
        play_button->ResetClick();
        ctx.setState(GameState::SELECTOR_MENU);
    }
    
}

void MainMenu::Render()
{
    window.clear();
    window.draw(backgroundSprite);

    for(auto &el: ui_elements)
        el->Render();

    window.display();
}

void MainMenu::Process()
{   
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    }
}


OptionsMenu::OptionsMenu(sf::RenderWindow &window, GameContext& ctx):
IMenu(window, ctx),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    float wx = window.getSize().x;
    float wy = window.getSize().y;

    back_button = new Button(window, "Back", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0});
    back_button->setPosition({wx/2, wy/2});

    ui_elements.push_back(back_button);

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void OptionsMenu::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            ctx.setState(GameState::MAIN_MENU);
        }
    }

    if (event->is<sf::Event::Closed>())
        window.close();

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->HandleClick(event);
    }

    if(back_button->WasClicked())
    {
        back_button->ResetClick();
        ctx.setState(ctx.getLastState());
    }
}

void OptionsMenu::Render()
{
    window.clear();
    window.draw(backgroundSprite);
    
    for(auto &el: ui_elements)
        el->Render();

    window.display();
}

void OptionsMenu::Process()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    }
}

SelectorMenu::SelectorMenu(sf::RenderWindow &window, GameContext& ctx):
IMenu(window, ctx),
backgroundSprite(*ResourceManager::getInstance().getTexture("img/back.jpg"))
{
    select_board_size = new Label(window, "select board size: ", 40.f, Colors::TITLE_COLOR, "fonts/shuriken.ttf", {0,0});
    select_game_type = new Label(window, "select game type: ", 40.f, Colors::TITLE_COLOR, "fonts/shuriken.ttf", {0,0});

    play_button = new Button(window, "Play", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false);
    back_button = new Button(window, "Back", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false);

    l_9x9 = new Button(window, "9 by 9", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false);
    l_13x13 = new Button(window, "13 by 13", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, true);
    l_19x19 = new Button(window, "19 by 19", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false);

    l_AI = new Button(window, "Play vs ai", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, true);
    l_LOCAL = new Button(window, "Play Locally", 40.f, Colors::BUTTON_COLOR, "fonts/robot-crush.ttf", {0,0}, false);

    curr_game_size = 13;
    curr_game_mode = GameType::AI;

    float mx = window.getSize().x/2;
    float my = window.getSize().y/2;

    select_board_size->setPosition({mx+10, my-400});
    select_game_type->setPosition({mx+10, my-100});
    play_button->setPosition({mx, my+200});
    back_button->setPosition({mx, my+300});

    l_9x9->setPosition({mx-250, my-300});
    l_13x13->setPosition({mx, my-300});
    l_19x19->setPosition({mx+250, my-300});

    l_AI->setPosition({mx-160, my});
    l_LOCAL->setPosition({mx+140, my});

    ui_elements.push_back(select_board_size);
    ui_elements.push_back(select_game_type);
    ui_elements.push_back(play_button);
    ui_elements.push_back(back_button);
    ui_elements.push_back(l_9x9);
    ui_elements.push_back(l_13x13);
    ui_elements.push_back(l_19x19);
    ui_elements.push_back(l_AI);
    ui_elements.push_back(l_LOCAL);

    sf::Color sprite_color = backgroundSprite.getColor();
    sprite_color.a = 80;
    backgroundSprite.setColor(sprite_color);
}

void SelectorMenu::EventHandler(const std::optional<sf::Event> &event)
{
    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
        {
            ctx.setState(GameState::MAIN_MENU);
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

    if(back_button->WasClicked())
    {
        ctx.setState(GameState::MAIN_MENU);
    }

    if(play_button->WasClicked())
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

    if(l_9x9->WasClicked())
    {
        l_13x13->setBorders(false);
        l_19x19->setBorders(false);

        l_9x9->setBorders(true);
        curr_game_size = 9;
    }

    if(l_13x13->WasClicked())
    {
        l_9x9->setBorders(false);
        l_19x19->setBorders(false);
        
        l_13x13->setBorders(true);
        curr_game_size = 13;
    }

    if(l_19x19->WasClicked())
    {
        l_9x9->setBorders(false);
        l_13x13->setBorders(false);
        
        l_19x19->setBorders(true);
        curr_game_size = 19;
    }

    if(l_AI->WasClicked())
    {
        l_LOCAL->setBorders(false);
        l_AI->setBorders(true);
        curr_game_mode = GameType::AI;
    }

    if(l_LOCAL->WasClicked())
    {
        l_AI->setBorders(false);
        l_LOCAL->setBorders(true);
        curr_game_mode = GameType::LOCAL;
    }

    for(IDrawable* el:ui_elements)
    {
        Button* btn = dynamic_cast<Button*>(el);
        if(btn != nullptr)
            btn->ResetClick();
    }
}

void SelectorMenu::Render()
{
    window.clear();
    window.draw(backgroundSprite);

    for(IDrawable* el:ui_elements)
    {
        el->Render();
    }

    window.display();
}

void SelectorMenu::Process()
{
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
    
    play_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
    back_button->colorOnHover(mouse_pos, Colors::TEXT_HOVER_COLOR);
}