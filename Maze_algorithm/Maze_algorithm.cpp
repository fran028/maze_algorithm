// Maze_algorithm.cpp : Defines the entry point for the application.
//

#include "Maze_algorithm.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
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
Position StartPosition(-1,-1);

bool CheckMazeLoaded() {
	if (Maze.size() > 0) {
		return true;
	}
	return false;
}

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

vector<string> SeparateStringByComa(string txt) {
	istringstream iss(txt);
	string value;
	vector<string> auxValues;
	while (getline(iss, value, ',')) {
		auxValues.push_back(value);
	}
	return auxValues;
}

void PrintMaze() {  

	for (int y = 0; y < Maze.size(); y++) {
		for (int x = 0; x < Maze[y].size(); x++) {
			char state = Maze[y][x].state;
			switch (state)
			{
				case 'f':
					cout << 'F';
					break;
				case 's':
					cout << 'S';
					break;
				case 'c':
					cout << '  ';
					break;
				default:
					cout << '[]';
					break;
			}
		}
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

	int finishCount = 0;
	int startCount = 0;
    string linea;  
    while (getline(leer, linea)) {
		vector<string> data = SeparateStringByComa(linea);
		int x = stoi(data[0]);
		int y = stoi( data[1]);
		char archState = data[2][0];
		 
		if (archState == 'w') {
			continue;
		}
		if (archState == 'f') {
			finishCount++;
		}
		if (archState == 's') {
			finishCount++;
			StartPosition.x = x;
			StartPosition.y = y;
		} 
		Maze[x][y].state = archState; 

    }
    leer.close();  
	PrintMaze();
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
		nextPos = NextMove(cell, lastCell);
	}  
	cell->tempMark = false;
	return salida;
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

int SolveOptions() {
	if (not CheckMazeLoaded()) {
		return 0;
	}
	cout << "-------------\n";
	cout << "Solving options\n";
	cout << "1) LIFO\n";
	cout << "2) FIFO\n";
	cout << "\nChoose option to solve menu: \n";
	int resp = 0;
	cin >> resp;
	int xs = StartPosition.x;
	int ys = StartPosition.y;
	bool result = false;
	switch (resp)
	{
	case 1:
		result = SolveMazeLIFO(&Maze[xs][ys], &Maze[xs][ys]);
		break;
	case 2:
		//result = SolveMazeFIFO(Maze[xs][ys]);
		cout << "\nThis option is no available yet. Sorry :(\n";
		break;
	default:
		cout << "The number chossen is not a valid option\n";
		break;
	}
	return 1;
}

void optionManager(int op) {
	int r;
	switch (op) {
	case 0:
		EndCredits();
		break;
	case 1:
		LoadMazeMap();
		break;
	case 2:
		r = SolveOptions();
		if (r) {
			cout << "There is no maze loaded to be solved.\n";
		}
		break;
	default:
		cout << "The number chossen is not a valid option\n";
		break;
	}
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


