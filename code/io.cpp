#include "io.h"
#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#elif __linux__
#include <ncurses.h>
#endif

void connect4_io::print(const std::string& output) {
#ifdef _WIN32
	std::cout << output;
#elif __linux__
	printw(output.c_str());
	refresh();
#endif
}

int connect4_io::getchar() {
	int input = 0;
#ifdef _WIN32
	input = _getch();
#elif __linux__
	input = getch();
	if (input == 27) {
		input = getch();
		input = getch();
	}
#endif

	return input;
}

void connect4_io::clear() {
#ifdef _WIN32
	system("cls");
#elif __linux__
	erase();
	refresh();
#endif
}

void connect4_io::reset() {
#ifdef _WIN32
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
#elif __linux__
	erase();
	refresh();
#endif
}

std::string connect4_io::getline() {
#ifdef _WIN32
	std::string input = "";
	std::getline(std::cin, input);
#elif __linux__
	echo();
	char raw_input[160];
	std::string input;
	getnstr(raw_input, 160);
	input = raw_input;
	noecho();
#endif
	return input;
}