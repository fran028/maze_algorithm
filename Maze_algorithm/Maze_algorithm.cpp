// Maze_algorithm.cpp : Defines the entry point for the application.
//

#include "Maze_algorithm.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;




class MazeCell {
	public:
		char state; //w,f,s,c
		bool tempMark;//treu o false
		int x; //int
		int y; //int
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

vector<vector<MazeCell>> Maze;


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

int LoadMazeMap() {
	string filename;
	cout << "Enter file name where maze is located with file type: ";
	cin >> filename;  
	int col, row;

	cout << "Enter number of columns of maze: ";
	cin >> col;
	cout << "Enter number of rows of maze: ";
	cin >> row;
	Maze.reserve(row);
	for (int i = 0; i < Maze.size(); ++i) {
		Maze[i].reserve(col);
		//use assign to fill all the maze with default wall
	}

	fstream leer(filename, ios::in);
    if (leer.fail()) {
        cout << "Maze file does not exist";
        return 0;
    }
    string linea;  
    while (getline(leer, linea)) {
		istringstream iss(linea);
		string value;
		vector<std::string> auxValues;
		while (getline(iss, value, ',')) {
			auxValues.push_back(value);
		}
		//check if type is not wall and only add the 'c','f' and 's' types
		//Also check if a 's' and 'f' types exist in file (f>=1 and s>=1)


    }
    leer.close();  
	return 1;
}

Position NextMove(MazeCell* cell, MazeCell* lastCell) {
	int dirH = cell->x - lastCell->x;
	int dirV = cell->y - lastCell->y;
	int x1 = -1;
	int y1 = -1;

	//derecha
	if (dirH == 0) {
		x1 = cell->x - dirV;
		y1 = cell->y;
	} else {
		x1 = cell->x;
		y1 = cell->y - dirH;
	}  
	if (Maze[x1][y1].state == 'c' && not Maze[x1][y1].tempMark) {
		Position nextPos(x1,y1);
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


bool SolveMazeLIFO(MazeCell *cell, MazeCell *lastCell) {  
	if (cell->state == 'f'){
		return true;
	}
	bool salida = false;
	cell->tempMark = true;
	Position nextPos = NextMove(cell, lastCell);
	while( (nextPos.x != -1 and nextPos.y!=-1) and not salida){
		salida = SolveMazeLIFO(&Maze[nextPos.x][nextPos.y], cell);
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


