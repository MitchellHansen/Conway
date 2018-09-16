#include "Node.h"

int Node::x_bound = 600;
int Node::y_bound = 600;

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

int Node::CurrentState() {
	return curr_state;
}

void Node::ShiftState() {
	curr_state = next_state;
}

bool Node::filled(std::vector<Node> *node_vec, sf::Vector2f np) {
 
    if (position.x + np.x < x_bound - 1 && position.x + np.x > -1  && 
        position.y + np.y < y_bound - 1 && position.y + np.y > -1) {

        return (node_vec->operator[](
                multi_to_linear(sf::Vector2i(position.x + np.x, position.y + np.y))
                ).CurrentState() != 0);
	}
}


void Node::Update(std::vector<Node> *node_vec) {
	
	int neighbors = 0;
	// x , y + 1
	// x + 1 , y
	// x , y - 1
	// x - 1 , y
    
    sf::Vector2f p1(position);
    
    if (filled(node_vec, sf::Vector2f(0,1)))
        neighbors += 1;

    if (filled(node_vec, sf::Vector2f(1,0)))
        neighbors += 1;

    if (filled(node_vec, sf::Vector2f(0,-1)))
        neighbors += 1;

    if (filled(node_vec, sf::Vector2f(-1,0)))
        neighbors += 1;

    // x + 1, y + 1
	// x + 1, y - 1
	// x - 1, y + 1
	// x - 1, y - 1

    if (filled(node_vec, sf::Vector2f(1, +1)))
        neighbors += 1;

    if (filled(node_vec, sf::Vector2f(1, -1)))
        neighbors += 1;

    if (filled(node_vec, sf::Vector2f(-1, +1)))
        neighbors += 1;

    if (filled(node_vec, sf::Vector2f(-1, -1)))
        neighbors += 1;

	if (neighbors == 3 || (neighbors == 2 && curr_state)) {
		next_state = true;
	}
	else if(rand()%900== 1)
		next_state = true;
    else
        next_state = false; 
}

sf::Vector2i Node::linear_to_multi(int position_) {
	return sf::Vector2i(position_ % x_bound, position_ / x_bound);
}

int Node::multi_to_linear(sf::Vector2i position) {
	return position.x * x_bound + position.y;
}
