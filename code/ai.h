#pragma once
#include <string>
#include "logic.h"

class ai
{
public:
	void set_ai_player(int player);
	void set_human_player(int player);
	void copy_board(std::string(&board)[6][7], std::string(&board_copy)[6][7]);
	bool place_piece_for_tree(int player, int column, std::string(&board)[6][7]);
	void minimax(std::string(&board)[6][7], int& column, int& value, int depth, int alpha, int beta, bool maximizing_player);
	void get_open_columns(int(&open_columns)[7], std::string board[6][7]);
	bool is_terminal_node(std::string board[6][7]);
	int score_position(std::string board[6][7], int player);
	int evaluate_window(std::string window[4], int player);
	void run_easy_bot(std::string(&board)[6][7]);
private:
	int ai_player = -1;
	int human_player = -1;
	logic logic_manager;
};
