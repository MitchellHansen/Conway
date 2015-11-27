#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <windows.h>
#include "Node.h"

const int WINDOW_X = 600;
const int WINDOW_Y = 800;

float elap_time() {
	static __int64 start = 0;
	static __int64 frequency = 0;

	if (start == 0) {
		QueryPerformanceCounter((LARGE_INTEGER*)&start);
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
		return 0.0f;
	}

	__int64 counter = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&counter);
	return (float)((counter - start) / double(frequency));
}

int main() {

	std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(0, 4);

	std::vector<Node> node_vec;

	for (int x = 0; x < Node::x_bound; x++) {
		for (int y = 0; y < Node::y_bound; y++) {
			node_vec.push_back(Node(sf::Vector2i(x, y)));
			if (rgen(rng) == 1) {
				node_vec.at(node_vec.size() - 1).Revive();
			}
		}
	}


	for (int i = 0; i < node_vec.size(); i++) {
		node_vec.at(i).ShiftState();
	}

	sf::RectangleShape live_node;
	sf::RectangleShape dead_node;

	live_node.setFillColor(sf::Color::Blue);
	dead_node.setFillColor(sf::Color::Green);

	live_node.setSize(sf::Vector2f(WINDOW_X / Node::x_bound, WINDOW_Y / Node::y_bound));
	dead_node.setSize(sf::Vector2f(WINDOW_X / Node::x_bound, WINDOW_Y / Node::y_bound));




	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Classic Games");

	float step_size = 0.0005f;
	double frame_time = 0.0, elapsed_time = 0.0, delta_time = 0.0, accumulator_time = 0.0, current_time = 0.0;


	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		elapsed_time = elap_time();
		delta_time = elapsed_time - current_time;
		current_time = elapsed_time;
		if (delta_time > 0.02f)
			delta_time = 0.02f;
		accumulator_time += delta_time;

		while ((accumulator_time - step_size) >= step_size) {
			accumulator_time -= step_size;
			
		}

		window.clear(sf::Color::Black);



		for (int i = 0; i < node_vec.size(); i++) {
			node_vec.at(i).Update(&node_vec);
		}

		for (int i = 0; i < node_vec.size(); i++) {
			node_vec.at(i).ShiftState();
		}

		for (int i = 0; i < node_vec.size(); i++) {
			if (node_vec.at(i).CurrentState() == true) {
				live_node.setPosition((i % Node::x_bound) * live_node.getGlobalBounds().width, (i / Node::x_bound) * live_node.getGlobalBounds().height);
				window.draw(live_node);
			}
			else {
				//dead_node.setPosition(i % Node::x_bound * dead_node.getGlobalBounds().width, i / Node::x_bound * dead_node.getGlobalBounds().height);
				//window.draw(live_node);
			}
		}
		
		window.display();



	}
	return 0;

}

