#include "game.h"

void Game::play(sf::RenderWindow& window)
{
	this->draw(window);
}

void Game::draw(sf::RenderWindow& window)
{
	board.draw_board(window);
	snake.update(moving_direction);
	snake.draw(window);

}

void Game::set_moving_direction(Snake::MovingDirection d)
{
	moving_direction = d;
}