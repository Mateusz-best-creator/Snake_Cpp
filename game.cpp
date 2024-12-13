#include "game.h"
#include <windows.h>
#include <iostream>
void Game::play(sf::RenderWindow& window)
{
	this->draw(window);
}

void Game::game_loop()
{
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