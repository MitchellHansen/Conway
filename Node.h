#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class Node {
public:
	static const int x_bound = 500;
	static const int y_bound = 500;

	Node(sf::Vector2i position_);
	Node(sf::Vector2i position_, std::vector<int> color);
	~Node();

	void Revive();
	int CurrentState();
	void ShiftState();
	void Update(std::vector<Node> *node_vec);
	void Dim();

	float r;
	float g;
	float b;
	float a;

	float b_r;
	float b_g;
	float b_b;
	float b_a;

private:

	sf::Vector2i linear_to_multi(int position_);
	int multi_to_linear(sf::Vector2i position);

	sf::Vector2i position;
	int curr_state;
	int next_state;



};


