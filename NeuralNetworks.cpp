#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cassert>
#include <random>
#include <iomanip>
#include <sstream>

void draw_graph(sf::RenderWindow& window, int length, std::vector<int> neurons, std::vector<std::vector<float>>);
std::vector<std::vector<float>> initialize_weights(int length, std::vector<int> neurons);

const int screen_width = 800, screen_height = 600;
const int font_size = 35;
const float radius = 35;

int main()
{
    //                                    width,        height
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "SFML works!");

    int neural_network_length = 3;
    std::vector<int> neural_network_neurons = { 2, 3, 1 };
    assert(neural_network_length = neural_network_neurons.size());
    std::vector<std::vector<float>> neuron_values = initialize_weights(neural_network_length, neural_network_neurons);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();
        draw_graph(window, neural_network_length, neural_network_neurons, neuron_values);
        window.display();
    }
}

float generate_random()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<float> distribution(0.0, 1.0);
    std::cout << "Random = " << distribution(generator) << std::endl;
    return distribution(generator);
}

std::vector<std::vector<float>> initialize_weights(int length, std::vector<int> neurons)
{
    std::vector<std::vector<float>> init_values(length);
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < neurons[i]; j++)
        {
            float random_value = generate_random();
            init_values[i].push_back(random_value);
        }
    }
    return init_values;
}

void draw_graph(sf::RenderWindow& window, int length, std::vector<int> neurons, std::vector<std::vector<float>> neuron_values)
{
    float min_neuron_value = 100, max_neuron_value = -100;
    for (int i = 0; i < neuron_values.size(); i++)
    {
        for (int j = 0; j < neuron_values[i].size(); j++)
        {
            if (min_neuron_value > neuron_values[i][j])
                min_neuron_value = neuron_values[i][j];
            if (max_neuron_value < neuron_values[i][j])
                max_neuron_value = neuron_values[i][j];
        }
    }
    float h_distance = screen_width / (1 + length);
    std::vector<float> v_distances;

    for (int i = 0; i < length; i++)
        v_distances.push_back(screen_height / (1 + neurons[i]));

    std::vector<std::vector<sf::Vector2f>> neuron_positions(length);
    sf::Font font;
    if (!font.loadFromFile("./Alphabet.ttf"))
    {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    // Step 1: Store neuron center positions (but don't draw yet)
    for (int i = 0; i < length; i++)
    {
        float x_position = h_distance * (i + 1);

        for (int j = 0; j < neurons[i]; j++)
        {
            float y_position = v_distances[i] * (j + 1);

            // Store the center position of the neuron (circle)
            neuron_positions[i].push_back(sf::Vector2f(x_position, y_position));
        }
    }

    // Step 2: Draw lines between neuron centers in adjacent layers
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < neurons[i]; j++)
        {
            for (int k = 0; k < neurons[i + 1]; k++)
            {
                // Draw a line between each neuron in layer i and each neuron in layer i+1
                sf::Vertex line[] =
                {
                    sf::Vertex(neuron_positions[i][j], sf::Color::White),
                    sf::Vertex(neuron_positions[i + 1][k], sf::Color::White)
                };
                window.draw(line, 2, sf::Lines); // Draw each line
            }
        }
    }

    // Step 3: Draw neurons (circles) and text on top of the lines
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < neurons[i]; j++)
        {
            float x_position = neuron_positions[i][j].x;
            float y_position = neuron_positions[i][j].y;

            // Draw the neuron (circle)
            sf::CircleShape shape(radius);
            shape.setOutlineColor(sf::Color(255, 255, 255));
            shape.setOutlineThickness(-2.5);
            float number = neuron_values.at(i).at(j);
            float color_range = (std::abs(number - min_neuron_value) / (max_neuron_value - min_neuron_value)) * 255;

            // Clamp the color_range to ensure it stays within [0, 255]
            color_range = std::max(0.0f, std::min(color_range, 255.0f));

            sf::Color c(color_range, 150, 150);
            shape.setFillColor(c);
            shape.setPosition(x_position - radius, y_position - radius);
            window.draw(shape);

            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << number;
            std::string roundedNumber = stream.str();

            // Draw the number as text inside the neuron (circle)
            sf::Text text;
            text.setFont(font);
            text.setString(roundedNumber);
            text.setCharacterSize(font_size);
            text.setFillColor(sf::Color::Black);
            text.setStyle(sf::Text::Bold);
            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.width / 2, textBounds.height / 2);
            text.setPosition(x_position, y_position - font_size / 2);

            window.draw(text);
        }
    }
}

