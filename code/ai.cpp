#include "ai.h"
#include <time.h>
#include <thread>
#include <chrono>

void ai::set_ai_player(int player)
{
	ai_player = player;
}

void ai::set_human_player(int player)
{
	human_player = player;
}

void ai::copy_board(std::string(&board)[6][7], std::string(&board_copy)[6][7]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board_copy[i][j] = board[i][j];
		}
	}
}

bool ai::place_piece_for_tree(int player, int column, std::string(&board)[6][7]) {
	column--;
	std::string player_slot = "";
	if (player == 1) {
		player_slot = " X |";
	}
	else if (player == 2) {
		player_slot = " O |";
	}

	if (board[0][column] == " . |") {
		for (int rows = 5; rows >= 0; rows--) {
			if (board[rows][column] == " . |") {
				board[rows][column] = player_slot;
				break;
			}
		}
		return false;
	}
	else {
		return true;
	}
}

void ai::minimax(std::string(&board)[6][7], int& column, int& value, int depth, int alpha, int beta, bool maximizing_player) {
	int open_columns[7];
	bool is_terminal = false;
	int num_open_columns = 0;
	std::string board_copy[6][7];
	int new_column;
	int new_value;

	get_open_columns(open_columns, board);

	is_terminal = is_terminal_node(board);

	if ((depth == 0) || is_terminal) {
		if (is_terminal) {
			if (logic_manager.check_winner(ai_player, board)) {
				column = -1;
				value = 10000000;
				return;
			}
			else if (logic_manager.check_winner(human_player, board)) {
				column = -1;
				value = -10000000;
				return;
			}
			else {
				column = -1;
				value = 0;
				return;
			}
		}
		else {
			column = -1;
			value = score_position(board, ai_player);
			return;
		}
	}

	srand(time(NULL));

	if (maximizing_player) {
		for (int i = 0; i < 7; i++) {
			if (open_columns[i] >= 0) {
				num_open_columns++;
			}
			else {
				break;
			}
		}
		value = -2147483647;
		column = open_columns[(int)(rand() % num_open_columns)];

		for (int i = 0; i < num_open_columns; i++) {
			copy_board(board, board_copy);
			place_piece_for_tree(ai_player, open_columns[i], board_copy);
			minimax(board_copy, new_column, new_value, depth - 1, alpha, beta, false);
			if (new_value > value) {
				value = new_value;
				column = open_columns[i];
			}
			if (value > alpha) {
				alpha = value;
			}

			if (alpha >= beta) {
				break;
			}
		}
		return;
	}
	else {
		for (int i = 0; i < 7; i++) {
			if (open_columns[i] >= 0) {
				num_open_columns++;
			}
			else {
				break;
			}
		}
		value = 2147483647;
		column = open_columns[(int)(rand() % num_open_columns)];

		for (int i = 0; i < num_open_columns; i++) {
			copy_board(board, board_copy);
			place_piece_for_tree(human_player, open_columns[i], board_copy);
			minimax(board_copy, new_column, new_value, depth - 1, alpha, beta, true);
			if (new_value < value) {
				value = new_value;
				column = open_columns[i];
			}
			if (value < beta) {
				beta = value;
			}

			if (alpha >= beta) {
				break;
			}
		}
		return;
	}

}

void ai::get_open_columns(int(&open_columns)[7], std::string board[6][7]) {
	int position = 0;
	for (int i = 0; i < 7; i++) {
		if (board[0][i] == " . |") {
			open_columns[position] = (i + 1);
			position++;
		}
	}

	for (position; position < 7; position++) {
		open_columns[position] = -1;
	}
}

bool ai::is_terminal_node(std::string board[6][7]) {
	bool player1_win = false;
	bool player2_win = false;
	bool tie = false;
	bool is_terminal = false;

	player1_win = logic_manager.check_winner(1, board);
	player2_win = logic_manager.check_winner(2, board);
	tie = logic_manager.cat_game(board);

	is_terminal = (player1_win || player2_win || tie);
	return is_terminal;
}

int ai::score_position(std::string board[6][7], int player) {
	int score = 0;
	std::string center_array[6];
	int center_count = 0;
	std::string row_array[6];
	std::string collumn_array[7];
	int rows = 6;
	int collumns = 7;
	std::string window[4];

	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < (collumns - 3); c++) {
			for (int i = 0; i < 4; i++) {
				window[i] = board[r][c + i];
			}
			score += evaluate_window(window, player);
		}
	}

	for (int c = 0; c < collumns; c++) {
		for (int r = 0; r < (rows - 3); r++) {
			for (int i = 0; i < 4; i++) {
				window[i] = board[r + i][c];
			}
			score += evaluate_window(window, player);
		}
	}

	for (int r = 3; r < rows; r++) {
		for (int c = 0; c < (collumns - 3); c++) {
			for (int i = 0; i < 4; i++) {
				window[i] = board[r - i][c + i];
			}
			score += evaluate_window(window, player);
		}
	}

	for (int r = 3; r < rows; r++) {
		for (int c = 3; c < collumns; c++) {
			for (int i = 0; i < 4; i++) {
				window[i] = board[r - i][c - i];
			}
			score += evaluate_window(window, player);
		}
	}

	return score;
}

int ai::evaluate_window(std::string window[4], int player) {
	std::string opponenet_piece = "";
	std::string player_piece = "";
	std::string empty_slot = " . |";
	if (player == 1) {
		opponenet_piece = " O |";
		player_piece = " X |";
	}
	else if (player == 2) {
		opponenet_piece = " X |";
		player_piece = " O |";
	}

	int score = 0;

	int player_piece_count = 0;
	int opponent_player_piece_count = 0;
	int empty_slot_count = 0;

	for (int i = 0; i < 4; i++) {
		if (window[i] == player_piece) {
			player_piece_count++;
		}

		if (window[i] == opponenet_piece) {
			opponent_player_piece_count++;
		}

		if (window[i] == empty_slot) {
			empty_slot_count++;
		}
	}

	if (player_piece_count == 4) {
		score = 100;
	}
	else if ((player_piece_count == 3) && (empty_slot_count == 1)) {
		score = 5;
	}
	else if ((player_piece_count == 2) && (empty_slot_count == 2)) {
		score = 2;
	}
	else if ((opponent_player_piece_count == 3) && (empty_slot_count == 1)) {
		score = -4;
	}

	return score;
}

void ai::run_easy_bot(std::string(&board)[6][7]) {
	srand(time(NULL));
	int upper_bound = 0;
	int lower_bound = 0;
	int zone = 0;
	bool column_full = false;
	int column = 0;
	zone = rand() % 6;
	if (((zone == 0) || (zone == 1) || (zone == 2) || (zone == 3)) && ((board[0][2] == " . |") || (board[0][3] == " . |") || (board[0][4] == " . |"))) {
		do {
			lower_bound = 2;
			upper_bound = 4;
			column = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
			column_full = logic_manager.place_piece(ai_player, column, board);
		} while (column_full);
	}
	else {
		do {
			if ((zone == 5) && ((board[0][0] == " . |") || (board[0][1] == " . |"))) {
				lower_bound = 0;
				upper_bound = 1;
			}
			else if ((zone == 6) && ((board[0][5] == " . |") || (board[0][6] == " . |"))) {
				lower_bound = 5;
				upper_bound = 6;
			}
			else {
				lower_bound = 0;
				upper_bound = 6;
			}
			column = (rand() % (upper_bound - lower_bound + 1)) + lower_bound;
			column_full = logic_manager.place_piece(ai_player, column, board);
		} while (column_full);
	}
}