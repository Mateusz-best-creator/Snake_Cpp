#include "board.h"
#include <iostream>

Board::Board()
{
    this->points = 0;
    if (font.loadFromFile("Alphabet.ttf"))
    {
        std::cerr << "Succesfully load Alphabet font..." << std::endl;
    }

    points_text.setFont(font);
    std::string score_text = "Points: " + std::to_string(this->points);
    points_text.setString(score_text);
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

    window.draw(vertical_lines);
    window.draw(horizontal_lines);
    window.draw(points_text);
}
