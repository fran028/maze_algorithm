#pragma once 
#include "MazeCell.h" 
#include "MazeCreation.h" 

#include <iostream>
using namespace std;

Position NextMove(MazeCell* cell, MazeCell* lastCell) {
	int dirH = cell->x - lastCell->x;
	int dirV = cell->y - lastCell->y;
	int x1 = -1;
	int y1 = -1;

	//derecha
	if (dirH == 0) {
		x1 = cell->x - dirV;
		y1 = cell->y;
	}
	else {
		x1 = cell->x;
		y1 = cell->y - dirH;
	}
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		Position nextPos(x1, y1);
		return nextPos;
	}

	//adelante 
	x1 = cell->x + dirV;
	y1 = cell->y + dirH;
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		Position nextPos(x1, y1);
		return nextPos;
	}

	//izquierda
	if (dirH == 0) {
		x1 = cell->x + dirV;
		y1 = cell->y;
	}
	else {
		x1 = cell->x;
		y1 = cell->y + dirH;
	}
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		Position nextPos(x1, y1);
		return nextPos;
	}

	Position nextPos(x1, y1);
	return nextPos;
}


bool SolveMazeLIFO(MazeCell* cell, MazeCell* lastCell) {
	if (cell->state == 'f') {
		return true;
	}
	bool salida = false;
	cell->tempMark = true;
	Position nextPos = NextMove(cell, lastCell);
	while ((nextPos.x != -1 and nextPos.y != -1) and not salida) {
		salida = SolveMazeLIFO(&Maze[nextPos.x][nextPos.y], cell);
		nextPos = NextMove(cell, lastCell);
	}
	cell->tempMark = false;
	return salida;
}


bool DetectIntersection(MazeCell* cell, MazeCell* lastCell){
	int dirH = cell->x - lastCell->x;
	int dirV = cell->y - lastCell->y;
	int x1 = -1;
	int y1 = -1;

	int numRoutes=0;

	//derecha
	if (dirH == 0) {
		x1 = cell->x - dirV;
		y1 = cell->y;
	}
	else {
		x1 = cell->x;
		y1 = cell->y - dirH;
	}
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		numRoutes++;
	}

	//adelante 
	x1 = cell->x + dirV;
	y1 = cell->y + dirH;
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		numRoutes++;
	}

	//izquierda
	if (dirH == 0) {
		x1 = cell->x + dirV;
		y1 = cell->y;
	}
	else {
		x1 = cell->x;
		y1 = cell->y + dirH;
	}
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		numRoutes++;
	}

	if (numRoutes > 1) {
		return true;
	}
	return false;
}

bool SolveMazeFIFO(MazeCell cell) {
	vector<MazeCell> queue;
	queue.push_back(cell);
	MazeCell currentPos = queue.front();
	MazeCell lastCell = currentPos;
	while (currentPos.state != 'f') {
		Position nextPos = NextMove(&cell, &lastCell);
		while ((nextPos.x != -1 and nextPos.y != -1)) {
			queue.push_back(Maze[nextPos.x][nextPos.y]);
			nextPos = NextMove(&cell, &lastCell);
		}
		lastCell = currentPos;
	}
	return true;
}