#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include <random>
#include "Node.h"
#include <thread>
#include <stack>

const int WINDOW_X = Node::x_bound;
const int WINDOW_Y = Node::y_bound;

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

bool inTriangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3, sf::Vector2f p){

    std::vector<float> v;
    
    float alpha = ((p2.y - p3.y)*(p.x - p3.x) + (p3.x - p2.x)*(p.y - p3.y)) /
                ((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
    v.push_back(alpha);

    float beta = ((p3.y - p1.y)*(p.x - p3.x) + (p1.x - p3.x)*(p.y - p3.y)) /
               ((p2.y - p3.y)*(p1.x - p3.x) + (p3.x - p2.x)*(p1.y - p3.y));
    v.push_back(beta);

    float gamma = 1.0f - alpha - beta;
    v.push_back(gamma);

    return std::all_of(v.cbegin(), v.cend(), [](int i){ return i > 0; });
}
    
bool inCircle(sf::Vector2f origin, float r, sf::Vector2f p) {
    return sqrt(pow(abs(origin.x - p.x), 2) + pow(abs(origin.y - p.y), 2)) < r;
}

float distFromCen(sf::Vector2f origin, sf::Vector2f p) {
    return sqrt(pow(abs(origin.x - p.x), 2) + pow(abs(origin.y - p.y), 2));
}

int main() {
	
    std::mt19937 rng(time(NULL));
	std::uniform_int_distribution<int> rgen(0, 19);

    srand(time(NULL));
	std::vector<Node> node_vec;

	// Init nodes, random value, push to front_stack
	for (int x = 0; x < Node::x_bound; x++) {
		for (int y = 0; y < Node::y_bound; y++) {
			
			Node node(sf::Vector2i(x, y));

            int varx = rand()%(20-3 + 1) + 3;
            int vary = rand()%(20-3 + 1) + 3;
//            11/3 is interesting
//            
			if ((x % 11 == 0) || (y % 3 == 0)) {

                node.Revive();
				node.b_r = 205;
                node.b_g = 190;
                node.b_b = 80;
                node.b_a = 255;

//				bool in_circle =  inCircle(sf::Vector2f(250,250), 186, sf::Vector2f(x,y));
//				if (in_circle){
//					node.Revive();		
//                   float dist = distFromCen(sf::Vector2f(250,250), sf::Vector2f(x,y));
//					node.b_r = std::min(255.0f, 90 + dist);
//					node.b_g = 190 - std::min(140.0f, dist);
//					node.b_b = 80;
//					node.b_a = 255;
//				}
			}
			
			node_vec.push_back(node);
		}
	}

	// Init window, and loop data
	sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Conway");
    window.setSize(sf::Vector2u(1200, 1200));
//    window.setPosition(sf::Vector2i(0, 1000));

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
			node_vec[i].Dim();
			
			pixel_array[i * 4] = node_vec[i].r; // R?
			pixel_array[i * 4 + 1] = node_vec[i].g; // G?
			pixel_array[i * 4 + 2] = node_vec[i].b; // B?
			pixel_array[i * 4 + 3] = node_vec[i].a; // A?


		}
		
		window.clear();

		texture.update(pixel_array);
		window.draw(sprite);

		window.display();



	}
	return 0;

}

