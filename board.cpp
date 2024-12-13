#include "board.h"
#include <iostream>
#include <cstdlib>

Board::Board()
{
    this->points = 0;
    if (font.loadFromFile("Alphabet.ttf"))
        std::cout << "Succesfully load Alphabet font..." << std::endl;
    else
    {
        std::cerr << "Cannot load font .ttf file\n";
        exit(0);
    }
    if (!fruit_texture.loadFromFile("fruit.png"))
    {
        std::cerr << "Cannot load font .ttf file\n";
        exit(0);
    }
    else
        std::cout << "Succesfully load fruit image..." << std::endl;
    fruit_texture.setSmooth(true);
    fruit_texture.setRepeated(false);
    fruit_square.setSize(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
    fruit_square.setTexture(&fruit_texture);

    points_text.setFont(font);
    points_text.setString("Points: " + std::to_string(this->points));
    points_text.setCharacterSize(SCORE_FONT_SIZE);
    points_text.setFillColor(this->font_color);
    points_text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - SCORE_FONT_SIZE, 30));
}

void Board::draw_board(sf::RenderWindow& window)
{
    sf::VertexArray vertical_lines(sf::Lines, NUMBER_VERTICAL_SQUARES * 2);
    sf::VertexArray horizontal_lines(sf::Lines, NUMBER_HORIZONTAL_SQUARES * 2);

    for (int i = 0; i < NUMBER_VERTICAL_SQUARES; i++)
    {
        double y_pos = SQUARE_HEIGHT * i + 200; // 200 beacuse we will use 200 upper pixels for displaying the score
        vertical_lines[i * 2] = sf::Vertex(sf::Vector2f(0, y_pos));
        vertical_lines[i * 2 + 1] = sf::Vertex(sf::Vector2f(SCREEN_WIDTH, y_pos));
    }
    for (int i = 0; i < NUMBER_HORIZONTAL_SQUARES; i++)
    {
        double x_pos = SQUARE_WIDTH * i;
        horizontal_lines[i * 2] = sf::Vertex(sf::Vector2f(x_pos, 200));
        horizontal_lines[i * 2 + 1] = sf::Vertex(sf::Vector2f(x_pos, SCREEN_HEIGHT));
    }
    //this->points++;
    for (int i = 0; i < fruits_points.size(); i++)
    {
        float x_pos = fruits_points[i].square_col * SQUARE_SIZE;
        float y_pos = 200 + fruits_points[i].square_row * SQUARE_SIZE;
        fruit_square.setPosition(sf::Vector2f(x_pos, y_pos));

        window.draw(fruit_square);
    }

    window.draw(vertical_lines);
    window.draw(horizontal_lines);
}

void Board::draw_top_info(sf::RenderWindow& window, const std::string& msg)
{
    points_text.setString("Points: " + std::to_string(points));
    if (msg.size())
        points_text.setString(msg);
    window.draw(points_text);
}

bool Board::check_fruit_snake_collision(Point& head)
{
    Point snake_head = head;
    std::cout << "Head = " << snake_head.square_col << " " << snake_head.square_row << std::endl;
    for (int i = 0; i < fruits_points.size(); i++)
    {
        int fruit_row = fruits_points[i].square_row;
        int fruit_col = fruits_points[i].square_col;
        if (snake_head.square_col == fruit_col &&
            snake_head.square_row == fruit_row)
        {
            fruits_points.erase(fruits_points.begin() + i);
            this->points++;
            return true;
        }
    }
    return false;
}