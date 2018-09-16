#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <random>
#include "Node.h"
#include <thread>
#include <stack>

const int WINDOW_X = 600;
const int WINDOW_Y = 600;

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

    Node::setX(WINDOW_X);
    Node::setY(WINDOW_Y);

    sf::Glsl::Vec4 aliveColor = sf::Color::Cyan;
	
    std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(0, 19);

	std::vector<Node> node_vec;


	// Init window, and loop data
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Conways");

	float step_size = 0.0005f;
	double frame_time = 0.0, elapsed_time = 0.0, delta_time = 0.0, accumulator_time = 0.0, current_time = 0.0;
	int frame_count = 0;

	std::stack<std::thread> thread_stack;

	sf::Uint8* pixel_array = new sf::Uint8[WINDOW_X * WINDOW_Y * 4];

	srand (time(NULL));	
	for (int i = 0; i < WINDOW_X * WINDOW_Y * 4; i += 4) {
		if (rand() % 10 == 5){
			pixel_array[i + 0] = sf::Color::Cyan.r; // R?
			pixel_array[i + 1] = sf::Color::Cyan.g; // G?
			pixel_array[i + 2] = sf::Color::Cyan.b; // B?
			pixel_array[i + 3] = 255; // A?
		} else {
			pixel_array[i + 0] = 0; // R?
			pixel_array[i + 1] = 0; // G?
			pixel_array[i + 2] = 0; // B?
			pixel_array[i + 3] = 0; // A?
		}
	}

	sf::Texture frontBuffer;
	sf::Texture backBuffer;

	frontBuffer.create(WINDOW_X, WINDOW_Y);
	frontBuffer.update(pixel_array);

	backBuffer.create(WINDOW_X, WINDOW_Y);
	backBuffer.update(pixel_array);

	sf::Sprite sprite(backBuffer);

	sf::Shader shader;
	
	shader.loadFromFile("../vertex.glsl", "../fragment.glsl");
	
	bool flipp = true;

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

		window.clear();
	
		shader.setUniform("alive_color", aliveColor);	
		shader.setUniform("backBuffer", backBuffer);
		shader.setUniform("frontBuffer", frontBuffer);	
		
		if (flipp) {
			flipp = false;
			sprite.setTexture(backBuffer);
		} else {
			flipp = true;
			sprite.setTexture(frontBuffer);
		}

	    shader.setUniform("flipp", flipp);	
		window.draw(sprite, &shader);
		window.display();
	}
	return 0;

}

