#include "game.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <cassert>

Game::Game()
{
    moving_direction = Snake::MovingDirection::RIGHT;
    sf::RectangleShape r1(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    sf::RectangleShape r2(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    sf::RectangleShape r3(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    sf::RectangleShape r4(sf::Vector2f(RECTANGLE_WIDTH, RECTANGLE_HEIGHT));
    r1.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 150));
    r2.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 350));
    r3.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 550));
    r4.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - RECTANGLE_WIDTH / 2, 750));

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
    int y_pos[4] = { 155, 355, 555, 755 };

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
        "Enjoy playing!";
    instruction_text.setString(t);
    sf::FloatRect textBounds = instruction_text.getLocalBounds();
    sf::Vector2f rectPosition = instruction_rectangle.getPosition();
    instruction_text.setPosition(
        rectPosition.x + (rectSize.x - textBounds.width) / 2 - textBounds.left,
        rectPosition.y + (rectSize.y - textBounds.height) / 2 - textBounds.top
    );
}

void Game::play(sf::RenderWindow& window)
{
	this->draw(window);
}

void Game::start_page()
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

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Num1:
                    current_state = States::START;
                    break;
                case sf::Keyboard::Num2:
                    current_state = States::REGISTER;
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

        // Render based on the current state
        switch (current_state)
        {
        case States::DEFAULT:
            // Draw start page options
            for (size_t i = 0; i < start_rectangles_options.size(); ++i)
            {
                window.draw(start_rectangles_options[i]);
                window.draw(texts[i]);
            }
            break;

        case States::START:
            // Close the current window and start the game loop
            window.close();
            this->game_loop();
            window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake - Mateusz Wieczorek"); // Reopen the window
            current_state = States::DEFAULT;
            break;

        case States::INSTRUCTION:
            // Draw instruction page
            window.draw(instruction_rectangle);
            window.draw(instruction_text);
            break;

        case States::REGISTER:
            break;

        case States::HALL_OF_FAME:
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