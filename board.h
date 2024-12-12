#pragma once


#include <vector>
#include "snake.h"

const int SCREEN_WIDTH = 700, SCREEN_HEIGHT = 900;
const sf::Color BACKGROUND_COLOR(144, 238, 144, 255);

class Board
{
private:
	const double SQUARE_HEIGHT = (SCREEN_HEIGHT - 200) / NUMBER_VERTICAL_SQUARES;
	const double SQUARE_WIDTH = SCREEN_WIDTH / NUMBER_HORIZONTAL_SQUARES;

	const int SCORE_FONT_SIZE = 100;
	int points;
	sf::Text points_text;
	sf::Font font;
	sf::Color font_color = sf::Color::White;

	Snake snake;

public:
	Board();
	void draw_board(sf::RenderWindow&);
};