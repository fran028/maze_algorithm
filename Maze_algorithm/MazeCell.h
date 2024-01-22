#pragma once 
#include <vector>

class MazeCell {
	public:
		char state= 'w'; //w,f,s,c
		bool passedBy=false;//treu o false
		int x=0; //int
		int y=0; //int

		MazeCell(){};

		MazeCell(char newState, int newX, int newY) {
			state = newState;
			passedBy = false;
			x = newX;
			y = newY;
		}
};

class QueueElement {
	public:	
		MazeCell currentPosition; //object 
		MazeCell lastPosition; //object
		QueueElement(MazeCell newCurrentPosition, MazeCell newLastPosition){
			currentPosition = newCurrentPosition;
			lastPosition = newLastPosition;
		}
};

class Position {
	public:
		int x;
		int y;  

		Position(int setx, int sety) {
			x = setx;
			y = sety;
		}
};

