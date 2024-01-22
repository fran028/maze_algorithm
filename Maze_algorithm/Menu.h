#pragma once

#include <iostream>
using namespace std;


void Menu() {
	cout << "-------------------------------------------" << endl;
	cout << "MAIN MENU" << endl;
	cout << "0) Exit" << endl;
	cout << "1) Load Maze" << endl;
	cout << "2) Solve Maze" << endl;
}

void EndCredits() {
	cout << "-------------------------------------------" << endl;
	cout << "Program closed" << endl;
	cout << "Thank you for playing" << endl;
	cout << "Made by: Franco Scarpettini" << endl;
}

void Options() {
	cout << "-------------------------------------------" << endl;
	cout << "Solving options" << endl;
	cout << "1) LIFO" << endl;
	cout << "2) FIFO" << endl;
	cout << "Choose option to solve menu:";
}