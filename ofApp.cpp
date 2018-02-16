#include "ofApp.h"
#include "Graph.h"
#include <algorithm>
#include <conio.h>

ofTrueTypeFont satanFont;
ofTrueTypeFont satanFontSmall;

int pathCounter;

const int rows = 15;
const int cols = 15;
// std::vector<std::vector<Graph*>> graph(rows);
Graph* graph = NULL;
Node* grid[rows][cols];

Node *start, *goal;

// Q to maintain nodes
std::deque<Node*> Q;
// path to maintain all the nodes between the path from start to goal
std::deque<Node*> path;

// Nodes' width and height
int w, h;

void generateGrid() {
	if (graph != NULL) {
		delete graph;
		graph = NULL;
	}
	// Create Nodes
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			bool isObstacle = true;
			if (ofRandom(0, 10) > 1) // 90% probability of not being an obstacle
				isObstacle = false;
			grid[i][j] = new Node(i * w, j * w, w, h, i * j, ofColor::white, isObstacle);
			
			if (graph == NULL)
				graph = new Graph(grid[0][0]);
			else
				graph->addNode(grid[i][j]);
		}
	}

	// Add Neighbours
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if ((i - 1) > 0)
				graph->connect(grid[i - 1][j], grid[i][j]);
			if (i + 1 < rows)
				graph->connect(grid[i + 1][j], grid[i][j]);
			if (j - 1 > 0)
				graph->connect(grid[i][j - 1], grid[i][j]);
			if (j + 1 < cols)
				graph->connect(grid[i][j + 1], grid[i][j]);
		}
	}
	int startX, startY, goalX, goalY;

	startX = ofRandom(rows);
	startY = ofRandom(cols);
	goalX = ofRandom(rows);
	goalY = ofRandom(cols);
	while (grid[goalX][goalY]->isObstacle) {
		goalX = ofRandom(rows);
		goalY = ofRandom(cols);
	}
	while (grid[startX][startY]->isObstacle) {
		startX = ofRandom(rows);
		startY = ofRandom(cols);
	}
	start = grid[startX][startY];
	goal = grid[goalX][goalY];

	std::cout << start->isObstacle << " " << goal->isObstacle << "   ";

	start->color = ofColor::green;
	goal->color = ofColor::blue;
}

//--------------------------------------------------------------
void ofApp::setup() {
	ofEnableSmoothing();
	// Get width and height of the nodes
	w = ofGetWidth() / rows;
	h = ofGetHeight() / cols;

	satanFont.load("Satan Possessed.ttf", 50);
	satanFontSmall.load("Satan Possessed.ttf", 10);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	if (graph) {
		if (pathCounter > 0) {
			path[pathCounter]->color = ofColor::red;
			start->color = ofColor::green;
			goal->color = ofColor::blue;
		}
		graph->draw();
		pathCounter--;
	}
	else {
		satanFont.drawString("Breadth-First-Search", 15, ofGetHeight() / 2);
		satanFontSmall.drawString("By: Ashar", ofGetWidth() / 2, ofGetHeight() - 20);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == GLFW_KEY_SPACE) {
		if (graph != NULL) {
			path = graph->Path_BFS(start, goal);
			pathCounter = path.size() - 1;
		}

	}
	else if (key == OF_KEY_RETURN)
		generateGrid();
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
