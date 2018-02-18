#ifndef GRAPH_H
#define GRAPH_H

#include "ofMain.h"
#include <vector>

class Node {
public:
	Node(float x, float y, float w, float h, int value, ofColor color, bool isObstacle = false);
	float x, y, w, h;
	int value;
	std::vector<Node*> edges;
	bool visited;
	Node* bfsParent;
	
	void draw();
	void drawEdges();
	void connect(Node* v);
	ofColor color;

	bool isObstacle;
};

class Graph {
public:
	Graph(Node* root);
	void connect(Node* u, Node* v);
	void addNode(Node* node);
	void draw();
	void setAllVisitedFlag(bool flag);
	std::vector<Node*> nodes;

	Node* BFS(Node* start, int value);
	std::deque<Node*> Path_BFS(Node* start, Node* goal);
};

#endif