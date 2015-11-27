#include "Node.h"



Node::Node(sf::Vector2i position_) {
	position = position_;
	curr_state = false;
	next_state = false;
}


Node::~Node() {
}

void Node::Revive() {
	next_state = true;
	curr_state = true;
}

bool Node::CurrentState() {
	return curr_state;
}

void Node::ShiftState() {
	curr_state = next_state;
}

void Node::Update(std::vector<Node> *node_vec) {
	
	int neighbors = 0;
	// x , y + 1
	// x + 1 , y
	// x , y - 1
	// x - 1 , y
	if (position.x     < x_bound - 1 && position.x     > -1 && position.y + 1 < y_bound - 1 && position.y + 1 > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x, position.y + 1))).CurrentState())
			neighbors++;
	}
	if (position.x + 1 < x_bound - 1 && position.x + 1 > -1 && position.y     < y_bound - 1 && position.y     > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x + 1, position.y))).CurrentState())
			neighbors++;
	}
	if (position.x     < x_bound - 1 && position.x     > -1 && position.y - 1 < y_bound - 1 && position.y - 1 > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x, position.y - 1))).CurrentState())
			neighbors++;
	}
	if (position.x - 1 < x_bound - 1 && position.x - 1 > -1 && position.y     < y_bound - 1 && position.y     > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x - 1, position.y))).CurrentState())
			neighbors++;
	}

	// x + 1, y + 1
	// x + 1, y - 1
	// x - 1, y + 1
	// x - 1, y - 1

	if (position.x + 1 < x_bound - 1 && position.x + 1 > -1 && position.y + 1 < y_bound - 1 && position.y + 1 > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x + 1, position.y + 1))).CurrentState())
			neighbors++;
	}
	if (position.x + 1 < x_bound - 1 && position.x + 1 > -1 && position.y - 1 < y_bound - 1 && position.y - 1 > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x + 1, position.y - 1))).CurrentState())
			neighbors++;
	}
	if (position.x - 1 < x_bound - 1 && position.x - 1 > -1 && position.y + 1 < y_bound - 1 && position.y + 1 > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x - 1, position.y + 1))).CurrentState())
			neighbors++;
	}
	if (position.x - 1 < x_bound - 1 && position.x - 1 > -1 && position.y - 1 < y_bound - 1 && position.y  - 1 > -1) {
		if (node_vec->at(multi_to_linear(sf::Vector2i(position.x - 1, position.y - 1))).CurrentState())
			neighbors++;
	}

	if (neighbors == 3 || (neighbors == 2 && curr_state)) {
		next_state = true;
	}
	else
		next_state = false;
}

sf::Vector2i Node::linear_to_multi(int position_) {
	return sf::Vector2i(position_ % x_bound, position_ / x_bound);
}

int Node::multi_to_linear(sf::Vector2i position) {
	return position.x * x_bound + position.y;
}
