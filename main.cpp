#include <SFML/Graphics.hpp>
#include <iostream>

const int SCREEN_WIDTH = 700, SCREEN_HEIGHT = 900;
const sf::Color BACKGROUND_COLOR(144, 238, 144, 255);

void draw_board(sf::RenderWindow&, sf::Text&);

int main()
{ 
    sf::Font font;
    if (font.loadFromFile("Alphabet.ttf"))
    {
        std::cout << "Succesfully load Alphabet font..." << std::endl;
    }
    const int SCORE_FONT_SIZE = 100;
    int score_points = 10;
    sf::Text text;
    text.setFont(font); // font is a sf::Font
    std::string score_text = "Points: " + std::to_string(score_points);
    text.setString(score_text);
    text.setCharacterSize(SCORE_FONT_SIZE);
    text.setFillColor(sf::Color::White);
    //text.setStyle(sf::Text::Bold);
    text.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - SCORE_FONT_SIZE, 30));

    //                                    width,        height
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Snake - Mateusz Wieczorek");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear(BACKGROUND_COLOR);
        draw_board(window, text);
        window.display();
    }
}

void draw_board(sf::RenderWindow& window, sf::Text& score_text)
{
    const int NUMBER_VERTICAL_SQUARES = 20;
    const int NUMBER_HORIZONTAL_SQUARES = 20;
    const double SQUARE_HEIGHT = (SCREEN_HEIGHT-200) / NUMBER_VERTICAL_SQUARES;
    const double SQUARE_WIDTH = SCREEN_WIDTH / NUMBER_HORIZONTAL_SQUARES;
    sf::VertexArray vertical_lines(sf::Lines, NUMBER_VERTICAL_SQUARES * 2);
    sf::VertexArray horizontal_lines(sf::Lines, NUMBER_HORIZONTAL_SQUARES *2);

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
    window.draw(score_text);
}