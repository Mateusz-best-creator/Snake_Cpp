#pragma once

#include <SFML/Graphics.hpp>

const int SQUARE_SIZE = 35;
const int NUMBER_VERTICAL_SQUARES = 20;
const int NUMBER_HORIZONTAL_SQUARES = 20;

struct Point
{
	int square_row, square_col;
};

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
	std::vector<Point> snake_squares;
	MovingDirection current_moving_direction;

public:
	Snake();
	Point update(MovingDirection);
	void draw(sf::RenderWindow&);
	bool lost();
};