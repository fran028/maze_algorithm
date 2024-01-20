#pragma once 
#include "MazeCell.h" 
#include "MazeCreation.h" 

#include <iostream>
using namespace std;

Position FirstMove(int x, int y){
	int x1, y1;
	//atras 
	x1 = x;
	y1 = y - 1;
	if (Maze[x1][y1].state == 'w') {
		Position nextPos(x1, y1);
		return nextPos;
	}
	//derecha
	x1 = x + 1;
	y1 = y; 
	if (Maze[x1][y1].state == 'w') {
		Position nextPos(x1, y1);
		return nextPos;
	}
	//adelante 
	x1 = x;
	y1 = y + 1;
	if (Maze[x1][y1].state == 'w') {
		Position nextPos(x1, y1);
		return nextPos;
	}
	//izquierda 
	x1 = x - 1;
	y1 = y; 
	if (Maze[x1][y1].state == 'w') {
		Position nextPos(x1, y1);
		return nextPos;
	}
}

Position NextMove(MazeCell* cell, MazeCell* lastCell) {
	int x1;
	int y1;
	
	int dirH = cell->x - lastCell->x;
	int dirV = cell->y - lastCell->y;
	if (dirH == 0 && dirV == 0) {
		Position f = FirstMove(cell->x, cell->y);
		cout << "First dir" << f.x << " , " << f.y << endl;
		dirH = cell->x - f.x;
		dirV = cell->y - f.y;
	}
	cout << dirH << " , " << dirV << endl;
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

	x1 = -1;
	y1 = -1;

	Position nextPos(x1, y1);
	return nextPos;
}


bool SolveMazeLIFO(MazeCell* cell, MazeCell* lastCell) {
	cout << endl;
	cout << "Last position " << lastCell->x << " , " << lastCell->y << endl;
	cout << "Current position " << cell->x << " , " << cell->y << endl;
	if (cell->state == 'f') {
		cout << "Exit founded on " << cell->x << " , " << cell->y << endl;
		return true;
	}
	bool salida = false;
	cell->tempMark = true;
	Position nextPos = NextMove(cell, lastCell);
	cout << "Next position " << nextPos.x << " , " << nextPos.y << endl;
	while ((nextPos.x != -1 and nextPos.y != -1) and not salida) {
		salida = SolveMazeLIFO(&Maze[nextPos.x][nextPos.y], cell);
		nextPos = NextMove(cell, lastCell);
		cout << "Next position " << nextPos.x << " , " << nextPos.y << endl;
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