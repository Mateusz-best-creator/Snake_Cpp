#pragma once

#include <SFML/Graphics.hpp>

const int NUMBER_VERTICAL_SQUARES = 20;
const int NUMBER_HORIZONTAL_SQUARES = 20;

class Snake
{
public:
	enum MovingDirection
	{
		LEFT = 'l',
		RIGHT = 'r',
		BOTTOM = 'b',
		TOP = 't',
	};

private:
	struct Point
	{
		int square_row, square_col;
	};
	const int SQUARE_SIZE = 35;
	std::vector<Point> temp_snake_squares;
	MovingDirection current_moving_direction = MovingDirection::RIGHT;

public:
	Snake();
	void update(MovingDirection);
	void draw(sf::RenderWindow&);
};