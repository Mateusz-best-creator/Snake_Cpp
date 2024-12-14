#pragma once

#include "board.h"
#include "snake.h"

const sf::Color StartRectangleColor(128, 128, 128, 255);

class Game
{
private:
	Board board;
	Snake snake;
	Snake::MovingDirection moving_direction;
	long long int duration_time = 0;
	const int TIME_TO_GENERATE_FRUIT = 3;

	// Constants about start page things location
	const int RECTANGLE_HEIGHT = 80;
	const int RECTANGLE_WIDTH = 220;
	std::vector<sf::RectangleShape> start_rectangles_options;

	// For text
	sf::Font font;
	sf::Color font_color = sf::Color::White;
	std::vector<sf::Text> texts;
	const int TEXT_FONT_SIZE = 50;

	// States for start page
	enum States 
	{
		START = 's',
		REGISTER = 'r',
		HALL_OF_FAME = 'h',
		INSTRUCTION = 'i',
		DEFAULT = 'd',
	};

	sf::RectangleShape instruction_rectangle{ sf::Vector2f(SCREEN_WIDTH - 100, SCREEN_HEIGHT - 200) };
	sf::Text instruction_text;
	const int INSTRUCTION_TEXT_SIZE = 50;

public:
	Game();

	void start_page();
	void game_loop(int level);
	void play(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void set_moving_direction(Snake::MovingDirection);
};