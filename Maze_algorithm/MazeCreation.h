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

void ResetMaze() {
	cout << "-------------------------------------------" << endl;
	cout << "Reseting maze" << endl;
	cout << "..." << endl;
	cout << endl;
	for (int y = 0; y < Maze.size(); y++) { 
		for (int x = 0; x < Maze[y].size(); x++) {
			Maze[x][y].passedBy = false; 
		} 
	}
	cout << "..." << endl;
	cout << "Mazed reseted" << endl;
	cout << "-------------------------------------------" << endl;
}

void PrintMaze() { 
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
				if (Maze[x][y].passedBy) {
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
	cout << "-------------------------------------------" << endl;
}

vector<string> SeparateStringByComa(string txt) {
	istringstream isString(txt);
	string value;
	vector<string> auxiliarValues;
	while (getline(isString, value, ',')) {
		auxiliarValues.push_back(value);
	}
	return auxiliarValues;
}

bool LoadMazeMap() {
	int auxiliarOption = -1;
	vector<string> files = GetMazesFiles();
	if (files.size() < 1) {
		return false;
	}
	cout << "-------------------------------------------" << endl;
	cout << "Files options\n";
	for (int i = 0; i < files.size(); ++i) {
		cout << i+1 << ") " << files[i] << endl;
		//use assign to fill all the maze with default wall
	}
	cout << files.size() << " files founded" <<endl;
	cout << "Choose maze: " << endl;
	do{
		cin >> auxiliarOption;
	} while ((auxiliarOption < 0) and (auxiliarOption > files.size()));
	string filename = files[auxiliarOption-1];

	fstream leer(filename, ios::in);
	if (not leer.is_open()) {
		cout << "There is no file with name '" << filename << "'\n";
		return false;
	}

	if (Maze.size() > 0) {
		cout << "Maze cleared";
		Maze.clear();
	}

	int columnMaze;
	int rowMaze;
	cout << "Enter number of columns of Maze: ";
	cin >> columnMaze;
	cout << "Enter number of rows of Maze: ";
	cin >> rowMaze; 
	Maze.resize(columnMaze +2);

	MazeCell defaultMazeCell('w', 0, 0);
	for (int i = 0; i < Maze.size(); ++i) {
		Maze[i].resize(columnMaze +2, defaultMazeCell);
		//use assign to fill all the maze with default wall
	}
	
	int finishCount = 0;
	int startCount = 0;
	string linea;
	while (getline(leer, linea)) {
		vector<string> data = SeparateStringByComa(linea);
		int xPosition = stoi(data[0]);
		int yPosition = stoi(data[1]);
		if (xPosition > columnMaze || yPosition > rowMaze) {
			cout << "The size of maze does not match the number of rows or coulmns previuosly passed" <<  endl;
			return false;
		}
		Maze[xPosition][yPosition].x = xPosition;
		Maze[xPosition][yPosition].y = yPosition;
		char fileCellType = data[2][0];

		if (fileCellType == 'w') {
			continue;
		}   
		if (fileCellType == 'f') {
			finishCount++;
		}
		if (fileCellType == 's') {
			startCount++;
			StartPosition.x = xPosition;
			StartPosition.y = yPosition;
		}
		Maze[xPosition][yPosition].state = fileCellType;
	}
	leer.close();
	if (finishCount < 1 or startCount < 1) {
		return false;
	}
	cout << "Starting Position:" << StartPosition.x << "," << StartPosition.y << endl;
	PrintMaze();
	return true;
}