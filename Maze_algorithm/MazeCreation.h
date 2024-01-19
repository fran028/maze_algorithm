#pragma once
#include "MazeCell.h"  
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
	string filename;
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
	cout << "Choose maze: ";
	do{
		cin >> auxOp;
	} while (auxOp >0 and auxOp< files.size());

	filename = files[auxOp];

	fstream leer(filename, ios::in);
	if (not leer.is_open()) {
		cout << "There is no file with name '" << filename << "'\n";
		return false;
	}
	int col, row;
	cout << "Enter number of columns of Maze: ";
	cin >> col;
	cout << "Enter number of rows of Maze: ";
	cin >> row;
	Maze.reserve(row);

	for (int i = 0; i < Maze.size(); ++i) {
		Maze[i].reserve(col);
		//use assign to fill all the maze with default wall
	}

	int finishCount = 0;
	int startCount = 0;
	string linea;
	while (getline(leer, linea)) {
		vector<string> data = SeparateStringByComa(linea);
		int x = stoi(data[0]);
		int y = stoi(data[1]);
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
	return true;
}