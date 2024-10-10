#include "neural_network.h"

#include <cassert>
#include <iomanip>

int main()
{
    //                                    width,        height
    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Neural Networks in C++");

    int neural_network_length = 3;
    /*std::cout << "Give number of layers in your neural network: ";
    std::cin >> neural_network_length;
    std::vector<int> neural_network_neurons;
    for (int i = 0; i < neural_network_length; i++)
    {
        int t;
        std::cout << "Neurons in " << i + 1 << " layer: ";
        std::cin >> t;
        neural_network_neurons.push_back(t);
    }
    //std::vector<float> inputs = { 1, 0 };
    std::vector<float> inputs;
    for (int i = 0; i < neural_network_neurons[0]; i++)
    {
        float t;
        std::cout << "Input " << i + 1 << " : ";
        std::cin >> t;
        inputs.push_back(t);
    }
    */
    std::vector<float> inputs = { 1, 0 };
    std::vector<int> neural_network_neurons = { 2, 3, 1 };
    assert(neural_network_length == neural_network_neurons.size());
    //assert(inputs.size() == neural_network_neurons[0]);
    NeuralNetwork nn(neural_network_neurons);
    //nn.forward_pass(inputs);
    //nn.backward_pass({1}); // We want 1 as our final answer
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        window.clear();

        // Training & drawing neural network
        nn.draw_graph(window);
        nn.forward_pass(inputs);
        nn.backward_pass({1});

        window.display();
    }
}
