#pragma once

#include <string>
#include "logic.h"
#include "ai.h"
#include "display.h"

#define ZERO 48;
#define ONE 49;
#define TWO 50;
#define THREE 51;
#define FOUR 52;
#define FIVE 53;
#define SIX 54;
#define SEVEN 55;

#ifdef _WIN32
#define ENTER 13
#define UP 72
#define DOWN 80
#elif __linux__
#define ENTER 10
#define UP 65
#define DOWN 66
#endif

class connect4_operations {

private:
	logic logic_manager;
	ai ai_manager;
	display display_manager;

public:
	void initialize_board(std::string(&board)[6][7]);
	void display_menu(int selection);
	void human_game_loop(std::string(&board)[6][7]);
	void hard_computer_game_loop(std::string(&board)[6][7]);
	void easy_computer_game_loop(std::string(&board)[6][7]);
	void moderate_computer_game_loop(std::string(&board)[6][7]);
};