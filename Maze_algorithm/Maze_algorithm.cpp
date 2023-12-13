// Maze_algorithm.cpp : Defines the entry point for the application.
//

#include "Maze_algorithm.h"
#include <iostream>
#include <vector>
using namespace std;


class MazeCell {
	public:
		char state;
		bool tempMark;
		int x;
		int y;
};

class Position {
	public: 
		int x;
		int y;
};


//MazeCell*  mazeMatrix[10][10];

/*MazeCell** mazeMatrix = nullptr;  // Pointer to the array of pointers
int rows = 5, columns = 10;

mazeMatrix = new MazeCell * [rows];  // Allocate memory for the array of pointers
for (int i = 0; i < rows; i++) {
	mazeMatrix[i] = new MazeCell[columns];  // Allocate memory for each row
}*/


void Menu() {
	cout << "-------------\n";
	cout << "MAIN MENU\n"; 
	cout << "0) Exit\n";
	cout << "1) Load Maze\n";
	cout << "2) Solve Maze\n";  
}

void EndCredits() { 
	cout << "Program closed \n";
	cout << "Thank you for playing \n";
	cout << "Made by: Franco Scarpettini \n"; 
}

void optionManager( int op) {  
	switch (op) {
	case 0:
		EndCredits();
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		cout << "The number chossen is not a valid option\n";
		break;
	} 
}

void LoadMazeMap() {
	string filename;
	cout << "Enter file name where maze is located: ";
	cin >> filename; 


}

Position NextMove(MazeCell* cell, MazeCell* lastCell) {
	int dirH = cell->x - lastCell->x;
	int dirV = cell->y - lastCell->y;

	//derecha
	if (dirH == 0) {
		int x1 = cell->x - dirV;
		int y1 = cell->y;
	}
	else {
		int x1 = cell->x;
		int y1 = cell->y - dirH;
	}  

	if (cell[x1][y1].state == 'c' && not cell[x1][y1].tempMark) {
		return (x1,y1)
	}

	//adelante 
	int x1 = cell->x + dirV;
	int y1 = cell->y + dirH; 

	if (cell[x1][y1].state == 'c' && not cell[x1][y1].tempMark) {
		return (x1, y1)
	}

	//izquierda
	if (dirH == 0) {
		int x1 = cell->x + dirV;
		int y1 = cell->y;
	}
	else {
		int x1 = cell->x;
		int y1 = cell->y + dirH;
	}

	if (cell[x1][y1].state == 'c' && not cell[x1][y1].tempMark) {
		return (x1, y1)
	}

	return (-1, -1);
}


bool SolveMazeLIFO(MazeCell *cell, MazeCell *lastCell) {
	
	bool salida = false;
	
	if (cell->state == 'f'){
		return true;
	}

	cell->tempMark = true;
	Position nextPos = NextMove(cell, lastCell);
	while(nextpos != (-1,-1) and not salida){
		salida = SolveMazeLIFO(cell[nextPos.x][nextPos.y], cell);
		Position nextPos = NextMove(cell, lastCell);
	}

	return salida;
}



int main(){
	Menu();
	int option;
	do { 
		cout << "Choose menu option: \n";
		cin >> option;
		optionManager(option);

	} while (option != 0);
	return 0;
}


