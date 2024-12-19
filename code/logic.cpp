#include "logic.h"

void logic::set_ai_player(int player)
{
	ai_player = player;
}

bool logic::check_winner(int player, std::string board[6][7]) {
	bool winner = false;
	bool rows = false;
	bool columns = false;
	bool diagonal = false;

	if ((last_ai_x_position >= 0) && (last_ai_y_position >= 0)) {
		(board[last_ai_y_position][last_ai_x_position])[0] = ' ';
		(board[last_ai_y_position][last_ai_x_position])[2] = ' ';
	}

	rows = rows_check_winner(player, board);
	columns = columns_check_winner(player, board);
	diagonal = diagonal_check_winner(player, board);

	if ((last_ai_x_position >= 0) && (last_ai_y_position >= 0)) {
		(board[last_ai_y_position][last_ai_x_position])[0] = '-';
		(board[last_ai_y_position][last_ai_x_position])[2] = '-';
	}

	if (rows || columns || diagonal) {
		winner = true;
	}

	return winner;
}

bool logic::rows_check_winner(int player, std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	std::string game_piece_slot = "";
	if (player == 1) {
		game_piece_slot = " X |";
	}
	else if (player == 2) {
		game_piece_slot = " O |";
	}
	bool winner = false;
	for (int rows = 0; rows < number_of_rows; rows++) {
		consecuative_pieces = 0;
		for (int columns = 0; columns < number_of_columns; columns++) {
			if (board[rows][columns] == game_piece_slot) {
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

bool logic::columns_check_winner(int player, std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	std::string game_piece_slot = "";
	if (player == 1) {
		game_piece_slot = " X |";
	}
	else if (player == 2) {
		game_piece_slot = " O |";
	}
	bool winner = false;
	for (int columns = 0; columns < number_of_columns; columns++) {
		consecuative_pieces = 0;
		for (int rows = 0; rows < number_of_rows; rows++) {
			if (board[rows][columns] == game_piece_slot) {
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

bool logic::diagonal_top_left_triangle_check_winner(int player, std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	std::string game_piece_slot = "";
	if (player == 1) {
		game_piece_slot = " X |";
	}
	else if (player == 2) {
		game_piece_slot = " O |";
	}
	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (starting_row + 1); i++) {
			if (board[starting_row - i][i] == game_piece_slot) {
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

bool logic::diagonal_bottom_left_triangle_check_winner(int player, std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	std::string game_piece_slot = "";
	if (player == 1) {
		game_piece_slot = " X |";
	}
	else if (player == 2) {
		game_piece_slot = " O |";
	}
	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (number_of_rows - starting_row); i++) {
			if (board[starting_row + i][i] == game_piece_slot) {
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

bool logic::diagonal_top_right_triangle_check_winner(int player, std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	std::string game_piece_slot = "";
	if (player == 1) {
		game_piece_slot = " X |";
	}
	else if (player == 2) {
		game_piece_slot = " O |";
	}
	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (starting_row + 1); i++) {
			if (board[starting_row - i][(number_of_columns - 1) - i] == game_piece_slot) {
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

bool logic::diagonal_bottom_right_triangle_check_winner(int player, std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	std::string game_piece_slot = "";
	if (player == 1) {
		game_piece_slot = " X |";
	}
	else if (player == 2) {
		game_piece_slot = " O |";
	}
	bool winner = false;
	for (int starting_row = 0; starting_row < number_of_rows; starting_row++) {
		consecuative_pieces = 0;
		for (int i = 0; i < (number_of_rows - starting_row); i++) {
			if (board[i + starting_row][(number_of_columns - 1) - i] == game_piece_slot) {
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

bool logic::diagonal_check_winner(int player, std::string board[6][7]) {
	bool diagonal = false;
	bool top_left = false;
	bool bottom_left = false;
	bool top_right = false;
	bool bottom_right = false;

	top_left = diagonal_top_left_triangle_check_winner(player, board);
	bottom_left = diagonal_bottom_left_triangle_check_winner(player, board);
	top_right = diagonal_top_right_triangle_check_winner(player, board);
	bottom_right = diagonal_bottom_right_triangle_check_winner(player, board);

	if (top_left || bottom_left || top_right || bottom_right) {
		diagonal = true;
	}
	return diagonal;
}

bool logic::cat_game(std::string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	std::string game_piece1_slot = " X |";
	std::string game_piece2_slot = " O |";
	bool cat_game = false;
	for (int rows = 0; rows < number_of_rows; rows++) {
		for (int columns = 0; columns < number_of_columns; columns++) {
			if ((board[rows][columns] == game_piece1_slot) || (board[rows][columns] == game_piece2_slot)) {
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

bool logic::place_piece(int player, int column, std::string(&board)[6][7]) {
	column--;
	std::string player_slot = "";
	if (player == 1) {
		player_slot = " X |";
	}
	else if (player == 2) {
		player_slot = " O |";
	}

	if (player == ai_player) {
		player_slot[0] = '-';
		player_slot[2] = '-';
		if ((last_ai_x_position >= 0) && (last_ai_y_position >= 0)) {
			(board[last_ai_y_position][last_ai_x_position])[0] = ' ';
			(board[last_ai_y_position][last_ai_x_position])[2] = ' ';
		}
	}

	if (board[0][column] == " . |") {
		for (int rows = 5; rows >= 0; rows--) {
			if (board[rows][column] == " . |") {
				board[rows][column] = player_slot;
				if (player == ai_player) {
					last_ai_x_position = column;
					last_ai_y_position = rows;
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