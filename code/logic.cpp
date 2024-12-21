#include "logic.h"

void logic::set_ai_player(int player)
{
	ai_player = player;
}

bool logic::check_winner(int player, const int (&board_data)[6][7]) {
	bool winner = false;
	bool rows = false;
	bool columns = false;
	bool diagonal = false;

	rows = rows_check_winner(player, board_data);
	columns = columns_check_winner(player, board_data);
	diagonal = diagonal_check_winner(player, board_data);

	if (rows || columns || diagonal) {
		winner = true;
	}

	return winner;
}

bool logic::rows_check_winner(int player, const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;

	bool winner = false;
	for (int rows = 0; rows < number_of_rows; rows++) {
		consecuative_pieces = 0;
		for (int columns = 0; columns < number_of_columns; columns++) {
			if (board_data[rows][columns] == player) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 4) {
				winner = true;
			}

		}
		if (consecuative_pieces == 4) {
			break;
		}

	}
	return winner;
}

bool logic::columns_check_winner(int player, const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;

	bool winner = false;
	for (int columns = 0; columns < number_of_columns; columns++) {
		consecuative_pieces = 0;
		for (int rows = 0; rows < number_of_rows; rows++) {
			if (board_data[rows][columns] == player) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 4) {
				winner = true;
			}
		}
		if (consecuative_pieces == 4) {
			break;
		}
	}
	return winner;
}

bool logic::diagonal_top_left_triangle_check_winner(int player, const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;

	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (starting_row + 1); i++) {
			if (board_data[starting_row - i][i] == player) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 4) {
				winner = true;
			}
		}
		if (consecuative_pieces == 4) {
			break;
		}
	}
	return winner;
}

bool logic::diagonal_bottom_left_triangle_check_winner(int player, const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;

	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (number_of_rows - starting_row); i++) {
			if (board_data[starting_row + i][i] == player) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 4) {
				winner = true;
			}
		}
		if (consecuative_pieces == 4) {
			break;
		}
	}
	return winner;
}

bool logic::diagonal_top_right_triangle_check_winner(int player, const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;

	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (starting_row + 1); i++) {
			if (board_data[starting_row - i][(number_of_columns - 1) - i] == player) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 4) {
				winner = true;
			}
		}
		if (consecuative_pieces == 4) {
			break;
		}
	}
	return winner;
}

bool logic::diagonal_bottom_right_triangle_check_winner(int player, const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;

	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (number_of_rows - starting_row); i++) {
			if (board_data[i + starting_row][(number_of_columns - 1) - i] == player) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 4) {
				winner = true;
			}
		}
		if (consecuative_pieces == 4) {
			break;
		}
	}
	return winner;
}

bool logic::diagonal_check_winner(int player, const int (&board_data)[6][7]) {
	bool diagonal = false;
	bool top_left = false;
	bool bottom_left = false;
	bool top_right = false;
	bool bottom_right = false;

	top_left = diagonal_top_left_triangle_check_winner(player, board_data);
	bottom_left = diagonal_bottom_left_triangle_check_winner(player, board_data);
	top_right = diagonal_top_right_triangle_check_winner(player, board_data);
	bottom_right = diagonal_bottom_right_triangle_check_winner(player, board_data);

	if (top_left || bottom_left || top_right || bottom_right) {
		diagonal = true;
	}
	return diagonal;
}

bool logic::cat_game(const int (&board_data)[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;

	bool cat_game = false;
	for (int rows = 0; rows < number_of_rows; rows++) {
		for (int columns = 0; columns < number_of_columns; columns++) {
			if ((board_data[rows][columns] == 1) || (board_data[rows][columns] == 2)) {
				consecuative_pieces++;
			}
			else {
				consecuative_pieces = 0;
			}
			if (consecuative_pieces == 42) {
				cat_game = true;
			}

		}
		if (consecuative_pieces == 42) {
			break;
		}

	}
	return cat_game;
}

bool logic::place_piece(int player, int column, int (&board_data)[6][7]) {
	column--;

	if (board_data[0][column] == 0) {
		for (int rows = 5; rows >= 0; rows--) {
			if (board_data[rows][column] == 0) {
				board_data[rows][column] = player;
				if (player == ai_player) {
					last_ai_column = column;
					last_ai_row = rows;
				}
				break;
			}
		}
		return false;
	}
	else {
		return true;
	}
}

int logic::get_last_ai_row()
{
	return last_ai_row;
}

int logic::get_last_ai_column()
{
	return last_ai_column;
}

void logic::reset_last_ai_position()
{
	last_ai_row = -1;
	last_ai_column = -1;
}