// main.cpp : Defines the entry point for the application.

#include "Maze_algorithm.h" 
#include "MazeCell.h" 
#include "SolvingAlgorithm.h"  
#include "MazeCreation.h"
#include "Menu.h"
#include "Timer.h"


void StartSolvingAlgorithm(string op) {

	bool result = false;
	int xs = StartPosition.x;
	int ys = StartPosition.y;
	double timeTaken = 0;
	ResetMaze();
	cout << "Solving algorithm using " << op << endl;
	if (op == "LIFO") {

		Timer lifoTimer;
		lifoTimer.start();
		result = SolveMazeLIFO(&Maze[xs][ys], &Maze[xs][ys]);
		lifoTimer.stop();
		timeTaken = lifoTimer.elapsedMicroseconds();
	} else if(op == "FIFO"){
		Timer fifoTimer;
		fifoTimer.start();
		result = SolveMazeFIFO(Maze[xs][ys]);
		fifoTimer.stop(); 
		timeTaken = fifoTimer.elapsedMicroseconds();
	}
	
	if (result) {
		cout << "Exit found" << endl;
		cout << "Time tacken: " << timeTaken << " Microseconds" << endl;
		cout << "Step tacken: " << CountStepInMaze() << endl;
		cout << "Stack: ";
		PrintStack();
	}
	else {
		cout << "Exit not found" << endl;
	}  
	cout << endl; 
	PrintMaze(); 

}


int SolveOptions() {
	if (Maze.size() <= 0) {
		return 0;
	}
	Options();
	int resp = 0;
	cin >> resp;
	//Runs the option chosen
	switch (resp)
	{
	case 1:
		StartSolvingAlgorithm("LIFO");
		break;
	case 2: 
		StartSolvingAlgorithm("FIFO"); 
		break;
	default:
		cout << "The number chossen is not an option" << endl;
		cout << "Please try again" << endl;
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
			if (not r) {
				cout << "There has been an error while loading the maze"<<endl;
				cout << "Please try again" << endl;
			}
			Menu();
			break;
		case 2:
			r = SolveOptions();
			if (r == 0) {
				cout << "There is no maze loaded to be solved." << endl;
			} 
			Menu();
			break;
		default:
			cout << "The number chossen is not a valid option" <<  endl;
			break;
	}
}

int main(){
	int option; 
	Menu();
	do {
		cout << "Choose menu option: ";
		cin >> option;
		optionManager(option);

	} while (option != 0);
	return 0;
}


