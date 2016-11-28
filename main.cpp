#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include "Node.h"
#include <thread>
#include <stack>

const int WINDOW_X = 300;
const int WINDOW_Y = 300;

float elap_time() {

	static std::chrono::time_point<std::chrono::system_clock> start;
	static bool started = false;

	if (!started) {
		start = std::chrono::system_clock::now();
		started = true;
	}

	std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_time = now - start;
	return static_cast<float>(elapsed_time.count());
}

void updateRange(std::vector<Node> *node_vec, int start_range_, int end_range_) {
	for (int i = start_range_; i < end_range_; i++) {
		node_vec->operator[](i).Update(node_vec);
	}
}



int main() {

	std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(0, 19);

	std::vector<Node> node_vec;

	// Init nodes, random value, push to front_stack
	for (int x = 0; x < Node::x_bound; x++) {
		for (int y = 0; y < Node::y_bound; y++) {
			node_vec.push_back(Node(sf::Vector2i(x, y)));
			if ((x % 5 == 0) || (y % 8 == 0)) {
				node_vec.at(node_vec.size() - 1).Revive();
			}
		}
	}

	// Init window, and loop data
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Classic Games");

	float step_size = 0.0005f;
	double frame_time = 0.0, elapsed_time = 0.0, delta_time = 0.0, accumulator_time = 0.0, current_time = 0.0;
	int frame_count = 0;

	std::stack<std::thread> thread_stack;

	sf::Uint8* pixel_array = new sf::Uint8[WINDOW_X * WINDOW_Y * 4];
	sf::Texture texture;
	texture.create(WINDOW_X, WINDOW_Y);
	sf::Sprite sprite(texture);

	
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Time keeping
		elapsed_time = elap_time();
		delta_time = elapsed_time - current_time;
		current_time = elapsed_time;
		if (delta_time > 0.02f)
			delta_time = 0.02f;
		accumulator_time += delta_time;

		while ((accumulator_time - step_size) >= step_size) {
			accumulator_time -= step_size;
			
			// Do nothing, FPS tied update()
		}

		for (int i = 0; i < 12; i++) {
			thread_stack.emplace(updateRange, &node_vec, (node_vec.size() / 12)* i, (node_vec.size() / 12)* (i + 1));
		}
		while (!thread_stack.empty()) {
			thread_stack.top().join();
			thread_stack.pop();
		}

		for (int i = 0; i < node_vec.size(); i++) {
			node_vec[i].ShiftState();
			if (node_vec[i].CurrentState() == true) {

				pixel_array[i * 4] = 112; // R?
				pixel_array[i * 4 + 1] = 190; // G?
				pixel_array[i * 4 + 2] = 249; // B?
				pixel_array[i * 4 + 3] = 255; // A?

			}
			else {
				pixel_array[i * 4] *= 0.999;// 49; // R?
				//pixel_array[i * 4 + 1] *= 0.999;//68; // G?
				pixel_array[i * 4 + 2] *= 0.999;//72; // B?
				pixel_array[i * 4 + 3] *= 0.999;//255; // A?
			}
		}
		
		window.clear();

		texture.update(pixel_array);
		window.draw(sprite);

		window.display();



	}
	return 0;

}

