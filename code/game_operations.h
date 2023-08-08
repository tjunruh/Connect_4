#pragma once

#include <string>
using namespace std;

#define ZERO 48;
#define ONE 49;
#define TWO 50;
#define THREE 51;
#define FOUR 52;
#define FIVE 53;
#define SIX 54;
#define SEVEN 55;

class connect4_operations {

private:
	int player_turn;
	int human_player;
	int ai_player;
	int last_ai_x_position = -1;
	int last_ai_y_position = -1;

public:
	void initialize_board(string(&board)[6][7]);
	void copy_board(string(&board)[6][7], string(&board_copy)[6][7]);
	bool place_piece(int player, int column, string(&board)[6][7]);
	bool place_piece_for_tree(int player, int column, string(&board)[6][7]);
	void print_board(string board[6][7]);
	bool check_winner(int player, string board[6][7]);
	bool rows_check_winner(int player, string board[6][7]);
	bool columns_check_winner(int player, string board[6][7]);
	bool diagonal_top_left_triangle_check_winner(int player, string board[6][7]);
	bool diagonal_bottom_left_triangle_check_winner(int player, string board[6][7]);
	bool diagonal_top_right_triangle_check_winner(int player, string board[6][7]);
	bool diagonal_bottom_right_triangle_check_winner(int player, string board[6][7]);
	bool diagonal_check_winner(int player, string board[6][7]);
	bool cat_game(string board[6][7]);
	void human_game_loop(string(&board)[6][7]);
	void hard_computer_game_loop(string(&board)[6][7]);
	void easy_computer_game_loop(string(&board)[6][7]);
	void moderate_computer_game_loop(string(&board)[6][7]);
	void minimax(string(&board)[6][7], int& column, int& value, int depth, int alpha, int beta, bool maximizing_player);
	void get_open_columns(int (&open_columns)[7], string board[6][7]);
	bool is_terminal_node(string board[6][7]);
	int score_position(string board[6][7], int player);
	int evaluate_window(string window[4], int player);
	int menu();
	void run_easy_bot(string(&board)[6][7]);
};