#include "Node.h"



Node::Node(sf::Vector2i position_) {
	position = position_;
	curr_state = false;
	next_state = false;
}

Node::Node(sf::Vector2i position_, std::vector<int> color) {
	position = position_;
	curr_state = false;
	next_state = false;

	b_r = color[0];
	b_g = color[1];
	b_b = color[2];
	b_a = color[3];

	r = 0;
	g = 0;
	b = 0;
	a = 0;
}


Node::~Node() {
}

void Node::Revive() {
	next_state = true;
	curr_state = true;
}

void Node::Dim() {

	if (CurrentState() == true) {
		r = b_r;
		g = b_g;
		b = b_b;
		a = b_a;
	} else {
		r *= 0.996;
		g *= 0.996;
		b *= 0.996;
		a *= 0.996;
	}
}

int Node::CurrentState() {
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
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x, position.y + 1))).CurrentState();
	}
	if (position.x + 1 < x_bound - 1 && position.x + 1 > -1 && position.y     < y_bound - 1 && position.y     > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x + 1, position.y))).CurrentState();
	}
	if (position.x     < x_bound - 1 && position.x     > -1 && position.y - 1 < y_bound - 1 && position.y - 1 > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x, position.y - 1))).CurrentState();
	}
	if (position.x - 1 < x_bound - 1 && position.x - 1 > -1 && position.y     < y_bound - 1 && position.y     > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x - 1, position.y))).CurrentState();
	}

	// x + 1, y + 1
	// x + 1, y - 1
	// x - 1, y + 1
	// x - 1, y - 1

	if (position.x + 1 < x_bound - 1 && position.x + 1 > -1 && position.y + 1 < y_bound - 1 && position.y + 1 > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x + 1, position.y + 1))).CurrentState();
	}
	if (position.x + 1 < x_bound - 1 && position.x + 1 > -1 && position.y - 1 < y_bound - 1 && position.y - 1 > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x + 1, position.y - 1))).CurrentState();
	}
	if (position.x - 1 < x_bound - 1 && position.x - 1 > -1 && position.y + 1 < y_bound - 1 && position.y + 1 > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x - 1, position.y + 1))).CurrentState();
	}
	if (position.x - 1 < x_bound - 1 && position.x - 1 > -1 && position.y - 1 < y_bound - 1 && position.y  - 1 > -1) {
		neighbors += node_vec->operator[](multi_to_linear(sf::Vector2i(position.x - 1, position.y - 1))).CurrentState();
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
