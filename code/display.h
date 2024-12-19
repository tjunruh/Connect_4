#pragma once
#include <string>

class display
{
public:
	void print_board(std::string board[6][7]);
	void menu(int selection);
	void display_logo();
};