# breadth-first-search
Breadth First Search implementation for pathfinding in a grid with visualizations using C++ and OpenFrameworks.

Controls - Press Enter to generate a new Grid.
         - Press Space to start finding the path for the generated grid.

The white rects show simple nodes.
The green rect shows the starting node. (The node where the search starts)
The blue rect shows the goal node. (The node to search)
The red rects show the shortest path from the start node to the goal node.

You can modify the grid easily - Just look at the generateGrid() function in ofApp.cpp
To modify things such as the outlines of the rects, look in Graph.h && Graph.cpp
