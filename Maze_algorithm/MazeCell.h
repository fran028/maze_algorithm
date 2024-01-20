#pragma once 
#include <vector>

class MazeCell {
	public:
		char state; //w,f,s,c
		bool tempMark;//treu o false
		int x; //int
		int y; //int

		MazeCell(char newState, int newX, int newY) {
			state = newState;
			tempMark = false;
			x = newX;
			y = newY;
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

