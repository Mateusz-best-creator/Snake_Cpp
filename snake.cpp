#include "snake.h"
#include <windows.h>
#include <iostream>
Snake::Snake()
{
    this->temp_snake_squares = { {10,8}, {10, 9}, {10, 10}, {10, 11} };

}

void Snake::update(MovingDirection d)
{
    current_moving_direction = d;
    int change_row = 0, change_col = 0;
    switch (current_moving_direction)
    {
    case Snake::LEFT:
        change_col--;
        break;
    case Snake::RIGHT:
        change_col++;
        break;
    case Snake::BOTTOM:
        change_row++;
        break;
    case Snake::TOP:
        change_row--;
        break;
    default:
        change_col++;
        break;
    }

    Point new_point = { 
        temp_snake_squares[temp_snake_squares.size()-1].square_row + 
        change_row, temp_snake_squares[temp_snake_squares.size() - 1].square_col + change_col
    };
    if (new_point.square_row >= NUMBER_HORIZONTAL_SQUARES)
        new_point.square_row = 0;
    if (new_point.square_row < 0)
        new_point.square_row = NUMBER_HORIZONTAL_SQUARES - 1;
    if (new_point.square_col >= NUMBER_VERTICAL_SQUARES)
        new_point.square_col = 0;
    if (new_point.square_col < 0)
        new_point.square_col = NUMBER_VERTICAL_SQUARES - 1;

    temp_snake_squares.erase(temp_snake_squares.begin());
    temp_snake_squares.push_back(new_point);
}

void Snake::draw(sf::RenderWindow& window)
{
    Sleep(120);
    std::vector<sf::RectangleShape> snake;
    for (int i = 0; i < temp_snake_squares.size(); i++)
    {
        snake.push_back(sf::RectangleShape(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE)));

        int x_pos = temp_snake_squares[i].square_col * SQUARE_SIZE;
        int y_pos = 200 + temp_snake_squares[i].square_row * SQUARE_SIZE;

        snake[i].setPosition(x_pos, y_pos);
        snake[i].setFillColor(sf::Color::Blue);
    }

    for (const auto& e : snake)
        window.draw(e);
}