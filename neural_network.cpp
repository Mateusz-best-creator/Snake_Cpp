#include "neural_network.h"

NeuralNetwork::NeuralNetwork(std::vector<int> neural_network_neurons)
{
    this->neurons = neural_network_neurons;
    this->network_length = neural_network_neurons.size();

    this->neuron_values = initialize_neuron_values(network_length, neural_network_neurons);

    // For 3 layers we want 2 set of weights
    for (int i = 0; i < this->neurons.size() - 1; i++)
    {
        int neuron_index = 0;
        std::map<int, std::vector<float>> temp_weights;
        std::vector<float> temp_vector;
        for (int j = 0; j < neurons[i] * neurons[i+1]; j++)
        {
            temp_vector.push_back(generate_random());
            if ((j + 1) % neurons[i + 1] == 0)
            {
                temp_weights[neuron_index++] = temp_vector;
                temp_vector.clear();
            }
        }
        this->weights.push_back(temp_weights);
    }

    for (int layer = 0; layer < weights.size(); ++layer) 
    {
        std::cout << "Layer " << layer << " weights:" << std::endl;
        for (const auto& neuron_pair : weights[layer]) 
        {
            int neuron_index = neuron_pair.first;  // The key in the map (neuron index)
            const std::vector<float>& neuron_weights = neuron_pair.second;  // The vector of weights
            std::cout << "  Neuron " << neuron_index << ": ";
            for (float weight : neuron_weights) 
            {
                std::cout << weight << " ";
            }

            std::cout << std::endl;
        }
    }
}

NeuralNetwork::~NeuralNetwork()
{

}

void NeuralNetwork::draw_graph(sf::RenderWindow& window)
{
    const int length = neurons.size();
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

float NeuralNetwork::generate_random()
{
    std::random_device rd;
    std::mt19937 generator(rd());
    std::normal_distribution<float> distribution(0.0, 1.0);
    return distribution(generator);
}

std::vector<std::vector<float>> NeuralNetwork::initialize_neuron_values(int length, std::vector<int> neurons)
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

float NeuralNetwork::forward_pass(std::vector<float> inputs)
{
    // Loop through each layer of the network
    for (int layer = 0; layer < network_length; layer++)
    {
        if (layer == 0)  // Input layer
        {
            for (int i = 0; i < inputs.size(); i++)
                neuron_values[0][i] = inputs[i];
        }
        else  // Hidden and output layers
        {
            float weighted_sum = 0.0f;
            for (int i = 0; i < neuron_values[layer].size(); i++)
            {
                int counter = 0;
                for (const auto& neuron_pair : weights[layer - 1])
                {
                    float input = neuron_values[layer - 1][counter];
                    weighted_sum += input * weights[layer - 1][counter][i];
                    std::cout << "Neuron in layer " << layer << " number: " << i << " input: " << input << " times " << weights[layer - 1][counter][i] << std::endl;
                    counter++;
                }
                neuron_values[layer][i] = weighted_sum;
                weighted_sum = 0.0f;
            }
        }
    }
    
    return neuron_values[network_length - 1][0];
}

float NeuralNetwork::backward_pass()
{
    return 1.0f;
}

float NeuralNetwork::activation_function(float x)
{
    return 1.0f / (1.0f + exp(-x));
}