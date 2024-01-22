#pragma once 

#include <stack> 
#include <iostream>
#include <queue>   
#include "MazeCell.h" 
#include "MazeCreation.h" 

using namespace std;

stack<MazeCell> stackLifo;
queue<QueueElement> queueFifo;  


int CountStepInMaze() {
	int totalAmount = 0;
	for (int yPosition = 0; yPosition < Maze.size(); yPosition++) {
		for (int xPosition = 0; xPosition < Maze[y].size(); xPosition++) {
			if (Maze[xPosition][yPosition].passedBy) {
				totalAmount++;
			}
		}
	}
	return totalAmount;
}
 

void PrintStack() {
	if (not stackLifo.empty()) {
		MazeCell topCell = stackLifo.top();
		stackLifo.pop();
		PrintStack();
		cout << "(" << topCell.x << "," << topCell.y << ")";
	} else {
		cout << endl;
	}
}

void PrintQueue() {
	while (not queueFifo.empty())
	{
		MazeCell currentPosition = queueFifo.front().currentPosition;
		cout << '(' << currentPosition.x << '-' << currentPosition.y << ')';
		queueFifo.pop();
	} 
	cout << endl;
}



Position FirstMove(int x, int y){
	int positionX, positionY;
	//atras 
	positionX = x;
	positionY = y - 1;
	if (Maze[positionX][positionY].state == 'w') {
		Position lastPosition(positionX, positionY);
		return lastPosition;
	}
	//derecha
	positionX = x + 1;
	positionY = y;
	if (Maze[positionX][positionY].state == 'w') {
		Position lastPosition(positionX, positionY);
		return lastPosition;
	}
	//adelante 
	positionX = x;
	positionY = y + 1;
	if (Maze[positionX][positionY].state == 'w') {
		Position lastPosition(positionX, positionY);
		return lastPosition;
	}
	//izquierda 
	positionX = x - 1;
	positionY = y;
	if (Maze[positionX][positionY].state == 'w') {
		Position lastPosition(positionX, positionY);
		return lastPosition;
	}

	positionX = x;
	positionY = y - 1;
	Position lastPosition(positionX, positionY);
	return lastPosition;
}

Position NextPossibleMove(MazeCell* cell, MazeCell* lastCell) {
	int positionX;
	int positionY;
	
	int dirH = cell->x - lastCell->x;
	int dirV = cell->y - lastCell->y;
	if (dirH == 0 && dirV == 0) {
		Position f = FirstMove(cell->x, cell->y); 
		dirH = cell->x - f.x;
		dirV = cell->y - f.y; 
	} 
	
	//derecha
	if (dirH == 0) {
		positionX = cell->x - dirV;
		positionY = cell->y;
	} else {
		positionX = cell->x;
		positionY = cell->y + dirH;
	}
	if (Maze[positionX][positionY].state != 'w' && not Maze[positionX][positionY].passedBy) {
		Position nextPos(positionX, positionY);
		return nextPos;
	}
	
	//adelante 
	positionX = cell->x + dirH;
	positionY = cell->y + dirV;
	if (Maze[positionX][positionY].state != 'w' && not Maze[positionX][positionY].passedBy) {
		Position nextPos(positionX, positionY);
		return nextPos;
	}
	//izquierda
	if (dirH == 0) {
		positionX = cell->x + dirV;
		positionY = cell->y;
	}
	else {
		positionX = cell->x;
		positionY = cell->y - dirH;
	}
	
	if (Maze[positionX][positionY].state != 'w' && not Maze[positionX][positionY].passedBy) {
		Position nextPos(positionX, positionY);
		return nextPos;
	}  

	//atras (when the maze starts in an itersection of four sides)
	positionX = cell->x - dirH;
	positionY = cell->y - dirV;
	if (Maze[positionX][positionY].state != 'w' && not Maze[positionX][positionY].passedBy) {
		Position nextPos(positionX, positionY);
		return nextPos;
	}
	
	positionX = -1;
	positionY = -1;
	Position nextPos(positionX, positionY);
	return nextPos;
}


bool SolveMazeLIFO(MazeCell* cell, MazeCell* lastCell) {  
	stackLifo.push(Maze[cell->x][cell->y]);
	if (cell->state == 'f') { 
		return true;
	}
	bool isExit = false;
	cell->passedBy = true;
	Position nextPosition = NextPossibleMove(cell, lastCell); 
	while ((nextPosition.x != -1 and nextPosition.y != -1) and not isExit) {
		isExit = SolveMazeLIFO(&Maze[nextPosition.x][nextPosition.y], cell);
		if (not isExit) {
			nextPosition = NextPossibleMove(cell, lastCell);
		} else if (nextPosition.x == -1 and nextPosition.y == -1) {
			stackLifo.pop();
		}
	} 
	return isExit;
}

bool SolveMazeFIFO(MazeCell cell) { 
	queueFifo.push(QueueElement(cell, cell));
	MazeCell currentPosition = queueFifo.front().currentPosition;
	MazeCell lastCell = queueFifo.front().lastPosition;
	Position nextPosition(0,0);
	do{
		currentPosition = queueFifo.front().currentPosition;
		lastCell = queueFifo.front().lastPosition;
		queueFifo.pop(); 
		do { 
			nextPosition = NextPossibleMove(&currentPosition, &lastCell);
			if (nextPosition.x != -1 and nextPosition.y != -1) {
				queueFifo.push(QueueElement(Maze[nextPosition.x][nextPosition.y], Maze[currentPosition.x][currentPosition.y]));
				Maze[nextPosition.x][nextPosition.y].passedBy = true;
			}
		} while ((nextPosition.x != -1 and nextPosition.y != -1));
	} while (currentPosition.state != 'f');
	PrintQueue();
	return true;
}