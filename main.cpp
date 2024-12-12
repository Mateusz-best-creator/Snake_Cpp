#include "game.h"

int main()
{ 
    Game game;
    //                                    width,        height
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake - Mateusz Wieczorek");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                    game.set_moving_direction(Snake::MovingDirection::TOP);
                else if (event.key.code == sf::Keyboard::Down)
                    game.set_moving_direction(Snake::MovingDirection::BOTTOM);
                else if (event.key.code == sf::Keyboard::Left)
                    game.set_moving_direction(Snake::MovingDirection::LEFT);
                else if (event.key.code == sf::Keyboard::Right)
                    game.set_moving_direction(Snake::MovingDirection::RIGHT);
            }
        }

        window.clear(BACKGROUND_COLOR);
        game.play(window);
        window.display();
    }
}
