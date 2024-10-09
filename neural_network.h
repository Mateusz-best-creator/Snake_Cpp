#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <iomanip>
#include <sstream>
#include <map>

const int screen_width = 800, screen_height = 600;

class NeuralNetwork
{
private:
	std::vector<int> neurons;
	int network_length;
	std::vector<std::vector<float>> neuron_values;

	// Initialize all weights randomly (from normal distibutoon)
	std::vector<std::map<int, std::vector<float>>> weights;

	const int font_size = 35;
	const float radius = 35;

public:
	NeuralNetwork(std::vector<int>);
	~NeuralNetwork();

	void draw_graph(sf::RenderWindow&);
	std::vector<std::vector<float>> initialize_neuron_values(int, std::vector<int>);
	float generate_random();

	float activation_function(float);
	float forward_pass(std::vector<float>);
	float backward_pass();
};