#include "game.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <cassert>

Game::Game()
{
    moving_direction = Snake::MovingDirection::RIGHT;
    
    // Start page content
    sf::RectangleShape r1(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    sf::RectangleShape r2(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    sf::RectangleShape r3(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    sf::RectangleShape r4(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    r1.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 100));
    r2.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 300));
    r3.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 500));
    r4.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 700));

    start_rectangles_options.push_back(r1);
    start_rectangles_options.push_back(r2);
    start_rectangles_options.push_back(r3);
    start_rectangles_options.push_back(r4);

    for (auto& e : start_rectangles_options)
    {
        e.setFillColor(StartRectangleColor);
        e.setOutlineThickness(3.f);
        e.setOutlineColor(sf::Color(30, 30, 30));
    }
    if (!font.loadFromFile("Alphabet.ttf"))
        exit(0);

    int i = 0;
    std::string texts_strings[4] = { "Start (1)", "Register (2)", "Hall Of Fame (3)", "Instructions (4)"};
    int y_pos[4] = { 105, 305, 505, 705 };

    for (int i = 0; i < start_rectangles_options.size(); ++i)
    {
        texts.push_back(sf::Text());
        texts[i].setFont(font);
        texts[i].setString(texts_strings[i]); 
        texts[i].setCharacterSize(TEXT_FONT_SIZE);
        texts[i].setFillColor(sf::Color::White);
        sf::FloatRect textBounds = texts[i].getLocalBounds();
        float textWidth = textBounds.width;
        float x_pos = (SCREEN_WIDTH - textWidth) / 2.0f;
        texts[i].setPosition(sf::Vector2f(x_pos, y_pos[i]));
    }
    assert(texts.size() == start_rectangles_options.size());

    // Instruction page content
    sf::Vector2f rectSize = instruction_rectangle.getSize();
    instruction_rectangle.setPosition(
        (SCREEN_WIDTH - rectSize.x) / 2, // Center horizontally
        (SCREEN_HEIGHT - rectSize.y) / 2  // Center vertically
    );
    instruction_rectangle.setFillColor(StartRectangleColor);
    instruction_text.setFont(font);
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setCharacterSize(INSTRUCTION_TEXT_SIZE);
    std::string t = "Welcome to the Snake Game!\n"
        "Use arrow keys to move.\n"
        "Collect food to get points.\n"
        "Register yourself and compete with others.\n"
        "Become the champion in the hall of fame!\n"
        "Enjoy playing!\n\n\n"
        "Click 'Escape' to go back.";
    instruction_text.setString(t);
    sf::FloatRect textBounds = instruction_text.getLocalBounds();
    sf::Vector2f rectPosition = instruction_rectangle.getPosition();
    instruction_text.setPosition(
        rectPosition.x + (rectSize.x - textBounds.width) / 2 - textBounds.left,
        rectPosition.y + (rectSize.y - textBounds.height) / 2 - textBounds.top
    );

    /*
        Registration page content
    */
    register_r.setPosition(50, 150);
    register_r.setOutlineThickness(3.0f);
    register_r.setOutlineColor(sf::Color::Black);
    name_text.setFont(font);
    name_text.setCharacterSize(INSTRUCTION_TEXT_SIZE);
    name_text.setFillColor(sf::Color::Black);

    name_text_start.setFont(font);
    name_text_start.setCharacterSize(INSTRUCTION_TEXT_SIZE);
    name_text_start.setFillColor(sf::Color::White);
}

void Game::play(sf::RenderWindow& window)
{
	this->draw(window);
}

void Game::main_page()
{
    States current_state = States::DEFAULT;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake - Mateusz Wieczorek");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape &&
                    current_state == States::DEFAULT))
                window.close();

            if (event.type == sf::Event::KeyPressed && current_state == States::REGISTER)
            {
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter)
                {
                    current_state = States::DEFAULT;
                    if (registered_name.size())
                    {
                        // Create new player or witch to existing
                        bool exist = false;
                        for (int i = 0; i < playing_players.size(); i++)
                        {
                            if (playing_players.at(i).name == registered_name)
                            {
                                std::cout << "Logging as: " << registered_name << std::endl;
                                player_player_index = i;
                                exist = true;
                                break;
                            }
                        }
                        if (!exist)
                        {
                            playing_players.push_back(Player(registered_name));
                            std::cout << "Creating new player: " << registered_name << std::endl;
                        }
                    }
                }
                else if (event.key.code == sf::Keyboard::Backspace)
                {
                    if (registered_name.size() > 0)
                        registered_name.erase(registered_name.begin() + registered_name.size() - 1);
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    registered_name += ' ';
                }
                else
                {
                    registered_name += static_cast<char>(97 + event.key.code);
                }
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Num1:
                    current_state = States::START;
                    break;
                case sf::Keyboard::Num2:
                    current_state = States::REGISTER;
                    // Reset registered name
                    this->registered_name.clear();
                    break;
                case sf::Keyboard::Num3:
                    current_state = States::HALL_OF_FAME;
                    break;
                case sf::Keyboard::Num4:
                    current_state = States::INSTRUCTION;
                    break;
                case sf::Keyboard::Escape:
                    current_state = States::DEFAULT;
                    break;
                default:
                    break;
                }
            }
        }
        window.clear(BACKGROUND_COLOR);

        // Bottom text
        sf::FloatRect textBounds = name_text_start.getLocalBounds();
        float textWidth = textBounds.width;
        float x = (SCREEN_WIDTH - textWidth) / 2.0f;

        // Render based on the current state
        switch (current_state)
        {
        case States::DEFAULT:
            for (size_t i = 0; i < start_rectangles_options.size(); ++i)
            {
                window.draw(start_rectangles_options[i]);
                window.draw(texts[i]);
            }
            
            if (registered_name.size() == 0)
                registered_name = "UNKNOWN";
            name_text_start.setString("You are logged as: " + registered_name);
            name_text_start.setPosition(sf::Vector2f(x, SCREEN_HEIGHT - 70));
            name_text_start.setFillColor(sf::Color::White);
            window.draw(name_text_start);
            
            break;

        case States::START:
            window.close();
            this->game_loop(1);
            window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake - Mateusz Wieczorek"); // Reopen the window
            current_state = States::DEFAULT;
            break;

        case States::INSTRUCTION:
            this->instruction_page(window);
            break;

        case States::REGISTER:
            this->registration_page(window);
            break;

        case States::HALL_OF_FAME:
            this->hall_of_fame_page(window);
            break;

        default:
            break;
        }
        window.display();
    }
}


void Game::game_loop(int level)
{
    auto start = std::chrono::high_resolution_clock::now();
    bool lost = false;

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake - Mateusz Wieczorek");
    while (window.isOpen() && !lost)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    moving_direction = Snake::MovingDirection::TOP;
                else if (event.key.code == sf::Keyboard::Down)
                    moving_direction = Snake::MovingDirection::BOTTOM;
                else if (event.key.code == sf::Keyboard::Left)
                    moving_direction = Snake::MovingDirection::LEFT;
                else if (event.key.code == sf::Keyboard::Right)
                    moving_direction = Snake::MovingDirection::RIGHT;
            }
        }

        if (snake.lost())
        {
            lost = true;
            board.draw_top_info(window, "You Lost!");
            window.display();
        }

        auto current_time = std::chrono::high_resolution_clock::now();
        duration_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start).count();
        if (duration_time > 0 && duration_time % TIME_TO_GENERATE_FRUIT == 0)
        {
            start = std::chrono::high_resolution_clock::now();
            board.add_fruit(snake.get_snake_squares());
        }

        window.clear(BACKGROUND_COLOR);
        play(window);
        window.display();
    }
}

void Game::draw(sf::RenderWindow& window)
{
    board.draw_board(window);
    board.draw_top_info(window, "");
    bool collision = board.check_fruit_snake_collision(snake.get_head());
    snake.update(moving_direction, collision);
	snake.draw(window);

}

void Game::set_moving_direction(Snake::MovingDirection d)
{
	moving_direction = d;
}

void Game::instruction_page(sf::RenderWindow& window)
{
    window.draw(instruction_rectangle);
    window.draw(instruction_text);
}

void Game::registration_page(sf::RenderWindow& window)
{
    name_text.setString(registered_name);
    sf::FloatRect r_textBounds = name_text.getLocalBounds();
    float textWidth = r_textBounds.width;
    float r_x_pos = (SCREEN_WIDTH - textWidth) / 2.0f;
    name_text.setPosition(sf::Vector2f(r_x_pos, 160));
    window.draw(register_r);
    window.draw(name_text);
}

int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}

void Game::hall_of_fame_page(sf::RenderWindow& window)
{
    std::vector<sf::RectangleShape> rectangles;
    int positions[5] = { 115, 265, 415, 565, 715 };
    sf::Color colors[5] = 
    {
        sf::Color(255, 215, 0),  // Gold
        sf::Color(192, 192, 192), // Silver
        sf::Color(205, 127, 50),  // Bronze
        sf::Color(135, 206, 250), // Light Blue
        sf::Color(255, 105, 180)  // Hot Pink
    };

    //std::cout << instruction_rectangle.getSize().x << " " << instruction_rectangle.getSize().y << std::endl;

    for (int i = 0; i < min(5, playing_players.size()); i++)
    {
        sf::Vector2f(SCREEN_WIDTH - 100, (SCREEN_HEIGHT - 200) / 5);
        rectangles.push_back(sf::RectangleShape(sf::Vector2f(SCREEN_WIDTH - 100, (SCREEN_HEIGHT - 200) / 5)));
        rectangles[i].setFillColor(colors[i]);
        rectangles[i].setOutlineThickness(1.f);
        rectangles[i].setOutlineColor(sf::Color(30, 30, 30));
        rectangles[i].setPosition(50, (SCREEN_HEIGHT - instruction_rectangle.getSize().y) / 2 + i * (instruction_rectangle.getSize().y / 5));
    }

    int change = instruction_rectangle.getSize().y / 5;
    int y_pos[5] = {};
    for (int i = 0; i < 5; i++)
        y_pos[i] = 110 + i * change;

    std::vector<sf::Text> texts_players;

    for (int i = 0; i < playing_players.size(); i++)
    {
        Player player = playing_players.at(i);
        std::string s = player.name + "\nPoints: " + std::to_string(player.points) + "\nGames Played: " + std::to_string(player.games_played) + "\n";

        texts_players.push_back(sf::Text());
        texts_players[i].setFont(font);
        texts_players[i].setString(s);
        texts_players[i].setCharacterSize(HALL_TEXT_FONT_SIZE);
        texts_players[i].setFillColor(sf::Color::White);
        sf::FloatRect textBounds = texts_players[i].getLocalBounds();
        float textWidth = textBounds.width;
        float x_pos = (SCREEN_WIDTH - textWidth) / 2.0f;
        texts_players[i].setPosition(sf::Vector2f(x_pos, y_pos[i]));
    }

    window.draw(instruction_rectangle);

    for (int i = 0; i < texts_players.size(); i++)
    {
        window.draw(rectangles[i]);
        window.draw(texts_players[i]);
    }
}