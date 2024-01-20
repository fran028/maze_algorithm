// Maze_algorithm.cpp : Defines the entry point for the application.
//
#include "Maze_algorithm.h" 
#include "MazeCell.h" 
#include "SolvingAlgorithm.h"  
#include "MazeCreation.h"
#include "Menu.h"


int SolveOptions() {
	if (Maze.size() <= 0) {
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
	//Runs the option chosen
	switch (resp)
	{
	case 1:
		cout << "Solving algorithm";
		result = SolveMazeLIFO(&Maze[xs][ys], &Maze[xs][ys]);
		if (result) {
			cout << "Exit found";
		} else {
			cout << "Exit not found";
		}
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
	// Runs the menu options and prints the result
	switch (op) {
		case 0:
			EndCredits();
			break;
		case 1:
			r = LoadMazeMap(); 
			if (r == 0) {
				cout << "Error while loading the maze"<<endl;
			}
			Menu();
			break;
		case 2:
			r = SolveOptions();
			if (r == 0) {
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


