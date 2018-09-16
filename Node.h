#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cstdlib>

class Node {
public:
	static int x_bound;
	static int y_bound;

    static void setX(int x){x_bound=x;};
    static void setY(int y){y_bound=y;};

	Node(sf::Vector2i position_);
	~Node();
	void Revive();
    bool filled(std::vector<Node> *node_vec, sf::Vector2f np);
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

