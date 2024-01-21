#pragma once 
#include <fstream> 
#include <string> 
#include <sstream> 
#include <iostream>
using namespace std;

#include "MazeCell.h" 
#include "MazesManager.h"

Position StartPosition(-1, -1);

vector<vector<MazeCell>> Maze;


void PrintMaze() {
	cout << "Imprimiendo laberinto" << endl;
	cout << "-------------------------------------------" << endl;
	cout << " +|"; 
	for (int j = 0; j < Maze[0].size(); j++) { 
		cout << j << "|";
	}
	cout << endl;
	for (int y = 0; y < Maze.size(); y++) {
		cout << setw(2) << y << "|";
		for (int x = 0; x < Maze[y].size(); x++) {
			char state = Maze[x][y].state;
			switch (state)
			{
			case 'f':
				cout << " F";
				break;
			case 's':
				cout << " S";
				break;
			case 'c':
				if (Maze[x][y].tempMark) {
					cout << " x";
				}
				else { 
					cout << "  ";
				}
				break;
			default:
				cout << "[]";
				break;
			}
		}
		cout << endl;
	}
	cout << "Laberinto impreso" << endl;
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

bool LoadMazeMap() {
	int auxOp = -1;
	vector<string> files = GetMazesFiles();
	if (files.size() < 1) {
		return false;
	}
	cout << "Files options\n";
	for (int i = 0; i < files.size(); ++i) {
		cout << i << ") " << files[i] << endl;
		//use assign to fill all the maze with default wall
	}
	cout << files.size() << " files founded" <<endl;
	cout << "Choose maze: " << endl;
	do{
		cin >> auxOp;
	} while ((auxOp < 0) and (auxOp >= files.size()));

	cout << "Option chosen: " << auxOp << " of " << files.size() << endl;
	string filename = files[auxOp];

	fstream leer(filename, ios::in);
	if (not leer.is_open()) {
		cout << "There is no file with name '" << filename << "'\n";
		return false;
	}

	if (Maze.size() > 0) {
		cout << "Maze cleared";
		Maze.clear();
	}

	int colMaze;
	int rowMaze;
	cout << "Enter number of columns of Maze: ";
	cin >> colMaze;
	cout << "Enter number of rows of Maze: ";
	cin >> rowMaze; 
	Maze.resize(colMaze+2);
	if (Maze.size() < 3) {
		cout << "Error in maze making (Reserve => " << Maze.size() << " )" << endl;
		return 0;
	}

	MazeCell defaultMazeCell('w', 0, 0);
	for (int i = 0; i < Maze.size(); ++i) {
		Maze[i].resize(colMaze+2, defaultMazeCell);
		//use assign to fill all the maze with default wall
	}
	
	int finishCount = 0;
	int startCount = 0;
	string linea;
	while (getline(leer, linea)) {
		vector<string> data = SeparateStringByComa(linea);
		int x = stoi(data[0]);
		int y = stoi(data[1]);
		Maze[x][y].x = x;
		Maze[x][y].y = y;
		char archState = data[2][0];

		if (archState == 'w') {
			continue;
		}
		if (archState == 'f') {
			finishCount++;
		}
		if (archState == 's') {
			startCount++;
			StartPosition.x = x;
			StartPosition.y = y;
		}
		Maze[x][y].state = archState;
	}
	leer.close();
	if (finishCount < 1 or startCount < 1) {
		return false;
	}
	cout << "Starting Position:" << StartPosition.x << "," << StartPosition.y;
	PrintMaze();
	return true;
}