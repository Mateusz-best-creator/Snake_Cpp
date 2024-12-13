#pragma once

#include "board.h"
#include "snake.h"

class Game
{
private:
	Board board;
	Snake snake;
	Snake::MovingDirection moving_direction;
	long long int duration_time = 0;
	const int TIME_TO_GENERATE_FRUIT = 3;

public:
	Game() = default;

	void game_loop();
	void play(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void set_moving_direction(Snake::MovingDirection);
};