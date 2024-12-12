#pragma once

#include "board.h"
#include "snake.h"

class Game
{
private:
	Board board;
	Snake snake;
	Snake::MovingDirection moving_direction;

public:
	Game() = default;

	void game_loop();
	void play(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void set_moving_direction(Snake::MovingDirection);
};