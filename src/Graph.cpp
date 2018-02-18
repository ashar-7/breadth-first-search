#include "Graph.h"
#include <deque>

Node::Node(float x, float y, float w, float h, int value, ofColor color, bool isObstacle) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->color = color;
	this->value = value;
	this->isObstacle = isObstacle;

	visited = false;
	bfsParent = NULL;
}

void Node::draw() {
	if (isObstacle)
		ofSetColor(0);
	else
		ofSetColor(color);

	ofFill();
	ofSetLineWidth(2);
	ofDrawRectangle(x, y, w, h);
	ofSetColor(255);
	ofNoFill();
	ofDrawRectangle(x, y, w, h);

	ofSetColor(255);
//	ofDrawBitmapString(ofToString(this->value), this->x, this->y + this->h);
}

void Node::connect(Node* v) {
	for (auto& node : edges) {
		if (node == v)
			return;
	}

	edges.push_back(v);
}

void Node::drawEdges() {
	for (auto& e : edges) {
		ofSetColor(0);
		ofNoFill();
		ofDrawLine(x, y, e->x, e->y);
	}
}

// -------------------------------------------------------------------------------------------

Graph::Graph(Node* root) {
	nodes.push_back(root);
}

void Graph::connect(Node* u, Node* v) {
	u->connect(v);
	v->connect(u);
}

void Graph::addNode(Node* node) {
	nodes.push_back(node);
}

void Graph::draw() {
	for (auto& n : nodes) {
		n->drawEdges();
	}
	for (auto& n : nodes) {
		n->draw();
	}
}

void Graph::setAllVisitedFlag(bool flag) {
	for (auto& n : nodes) {
		n->visited = flag;
	}
}

Node* Graph::BFS(Node* start, int value) {
	setAllVisitedFlag(false);

	std::queue<Node*> Q;

	Q.push(start);
	start->visited = true;

	while (Q.empty() != true) {
		Node* current = Q.front();
		Q.pop();

		for (auto& neighbour : current->edges) {
			if (neighbour->visited != true) {
				Q.push(neighbour);
				neighbour->visited = true;
			}

			if (neighbour->value == value) {
				return neighbour;
			}
		}
	}
}

std::deque<Node*> Graph::Path_BFS(Node* start, Node* goal) {
	setAllVisitedFlag(false);
	// Q to maintain nodes
	std::deque<Node*> Q;
	// path to maintain all the nodes between the path from start to goal
	std::deque<Node*> path;

	Q.push_back(start);

	while (Q.empty() != true) {
		Node* parent = Q.front();
		Q.pop_front();

		std::cout << "parent: " << parent->value << "\n";

		if (parent == goal) {
			// Construct Path
			path.push_back(parent);
			Node* temp = parent->bfsParent;
			while (temp != NULL) {
				path.push_back(temp);
				temp = temp->bfsParent;
			}
			printf("Goal Found!\n");
			return path;
		}
		
		for (auto& child : parent->edges) {
			std::cout << "child : " << child->value << "\n";
			if (child->visited || child->isObstacle)
				continue;
			// Check if child is in the queue
			bool found = false;
			for (auto& node : Q) {
				if (node == child) {
					found = true;
					break;
				}
			}
			if (!found) {
				child->bfsParent = parent;
				Q.push_back(child);
			}
		}

		parent->visited = true;
	}

	return path;
}

