#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class Node {
public:
	static const int x_bound = 300;
	static const int y_bound = 300;

	Node(sf::Vector2i position_);
	~Node();

	void Revive();
	int CurrentState();
	void ShiftState();
	void Update(std::vector<Node> *node_vec);

private:

	sf::Vector2i linear_to_multi(int position_);
	int multi_to_linear(sf::Vector2i position);

	sf::Vector2i position;
	int curr_state;
	int next_state;


};

