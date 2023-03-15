#include "game_operations.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include <time.h>
using namespace std;

void connect4_operations::initialize_board(string (&board)[6][7]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board[i][j] = " . |";
		}
	}
}

void connect4_operations::copy_board(string(&board)[6][7], string(&board_copy)[6][7]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board_copy[i][j] = board[i][j];
		}
	}
}


bool connect4_operations::place_piece(int player, int column, string (&board)[6][7]) {
	column--;
	string player_slot = "";
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

bool connect4_operations::place_piece_for_tree(int player, int column, string(&board)[6][7]) {
	column--;
	string player_slot = "";
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

void connect4_operations::print_board(string board[6][7]) {
	string board_to_print = "";
	for (int g = 0; g < 7; g++) {
		board_to_print = board_to_print + (" " + to_string(g + 1) + "  ");
	}
	board_to_print = board_to_print + "\n____________________________\n";

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board_to_print = board_to_print + board[i][j];
		}
		board_to_print = board_to_print + "\n";
	}

	board_to_print = board_to_print + "============================\n\n";
	cout << board_to_print << endl;
}

bool connect4_operations::check_winner(int player, string board[6][7]) {
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

bool connect4_operations::rows_check_winner(int player, string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece_slot = "";
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

bool connect4_operations::columns_check_winner(int player, string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece_slot = "";
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

bool connect4_operations::diagonal_top_left_triangle_check_winner(int player, string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece_slot = "";
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

bool connect4_operations::diagonal_bottom_left_triangle_check_winner(int player, string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece_slot = "";
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

bool connect4_operations::diagonal_top_right_triangle_check_winner(int player, string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece_slot = "";
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

bool connect4_operations::diagonal_bottom_right_triangle_check_winner(int player, string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece_slot = "";
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

bool connect4_operations::diagonal_check_winner(int player, string board[6][7]) {
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

bool connect4_operations::cat_game(string board[6][7]) {
	int consecuative_pieces = 0;
	int number_of_rows = 6;
	int number_of_columns = 7;
	string game_piece1_slot = " X |";
	string game_piece2_slot = " O |";
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

void connect4_operations::human_game_loop(string (&board)[6][7]) {
	string p1_username = "";
	string p2_username = "";
	bool winner = false;
	bool tie = false;
	bool column_exist = false;
	bool column_full = false;
	int input = 0;
	int column = 0;
	player_turn = 1;
	ai_player = -1;
	human_player = -1;

	cout << "Connect 4: \n\n";
	cout << "Type in your player name, player 1.\n" << endl;
	getline(cin >> ws, p1_username);
	cout << "Type in your player name, player 2\n" << endl;
	getline(cin >> ws, p2_username);

	system("CLS");
	while ((winner == false) && (tie == false)) {
		system("CLS");
		print_board(board);

		do {
			if (player_turn == 1) {
				cout << p1_username + ":\nPlace a piece by typing which column.\n";
			}
			else {
				cout << p2_username + ":\nPlace a piece by typing which column.\n";
			}
			input = _getch();
			column = input - 48;
			if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
				cout << "Column does not exist.\n" << endl;
				column_exist = false;
			}
			else {
				column_full = place_piece(player_turn, column, board);
				column_exist = true;
			}

		} while (column_full || !column_exist);

		winner = check_winner(player_turn, board);
		if (winner) {
			system("CLS");
			print_board(board);
			if (player_turn == 1) {
				cout << p1_username + " won!\n";
			}
			else {
				cout << p2_username + " won\n";
			}
		}
		tie = cat_game(board);
		if (tie) {
			system("CLS");
			print_board(board);
			cout << "cat game\n" << endl;
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

void connect4_operations::minimax(string (&board)[6][7], int& column, int& value, int depth, int alpha, int beta, bool maximizing_player) {
	int open_columns[7];
	bool is_terminal = false;
	int num_open_columns = 0;
	string board_copy[6][7];
	int new_column;
	int new_value;

	get_open_columns(open_columns, board);

	is_terminal = is_terminal_node(board);

	if ((depth == 0) || is_terminal) {
		if (is_terminal) {
			if (check_winner(ai_player, board)) {
				column = -1;
				value = 10000000;
				return;
			}
			else if (check_winner(human_player, board)) {
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

void connect4_operations::get_open_columns(int open_columns[7], string board[6][7]) {
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

bool connect4_operations::is_terminal_node(string board[6][7]) {
	bool player1_win = false;
	bool player2_win = false;
	bool tie = false;
	bool is_terminal = false;

	player1_win = check_winner(1, board);
	player2_win = check_winner(2, board);
	tie = cat_game(board);

	is_terminal = (player1_win || player2_win || tie);
	return is_terminal;
}

int connect4_operations::score_position(string board[6][7], int player) {
	int score = 0;
	string center_array[6];
	int center_count = 0;
	string row_array[6];
	string collumn_array[7];
	int rows = 6;
	int collumns = 7;
	string window[4];

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

int connect4_operations::evaluate_window(string window[4], int player) {
	string opponenet_piece = "";
	string player_piece = "";
	string empty_slot = " . |";
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

void connect4_operations::hard_computer_game_loop(string(&board)[6][7]) {
	using namespace std::this_thread;
	using namespace std::chrono;
	int input = 0;
	string human_user_name = "";
	bool winner = false;
	bool tie = false;
	int column = 0;
	bool column_exist = false;
	bool column_full = false;
	int ai_drop_column = 0;
	int ai_value = 0;
	int alpha = -2147483647;
	int beta = 2147483647;
	player_turn = 1;
	last_ai_x_position = -1;
	last_ai_y_position = -1;

	cout << "Would you like to go first or second (type 1 or 2)?" << endl;
	while ((input != 1) && (input != 2)) {
		input = _getch() - 48;
	}
	
	human_player = input;
	if (human_player == 1) {
		ai_player = 2;
	}
	else if (human_player == 2) {
		ai_player = 1;
	}

	cout << "Type in your player name." << endl;
	getline(cin >> ws, human_user_name);
	
	system("CLS");
	while ((winner == false) && (tie == false)) {
		system("CLS");
		print_board(board);

		if (player_turn == human_player) {
			cout << human_user_name + ":\nPlace a piece by typing which column.\n";
			do {
				input = _getch();
				column = input - 48;
				if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
					cout << "Column does not exist.\n" << endl;
					column_exist = false;
				}
				else {
					column_full = place_piece(player_turn, column, board);
					column_exist = true;
				}

			} while (column_full || !column_exist);
		}
		else {
			cout << "Computer:\nPlace a piece by typing which column.\n";
			minimax(board, ai_drop_column, ai_value, 7, alpha, beta, true);
			sleep_for(3500ms);
			place_piece(ai_player, ai_drop_column, board);
		}
		

		winner = check_winner(player_turn, board);
		if (winner) {
			system("CLS");
			print_board(board);
			if (player_turn == human_player) {
				cout << human_user_name + " won!\n";
			}
			else {
				cout << "Computer won!\n";
			}
		}
		tie = cat_game(board);
		if (tie) {
			system("CLS");
			print_board(board);
			cout << "cat game\n" << endl;
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

int connect4_operations::menu() {
	system("CLS");
	cout << "Welcome to Connect 4 console version!\n\n" << endl;
	cout << "Pick a game mode:\n" << endl;
	cout << "MULTIPLAYER" << endl;
	cout << "0 -> multiplayer" << endl;
	cout << "SINGLE PLAYER" << endl;
	cout << "1 -> easy" << endl;
	cout << "2 -> moderate" << endl;
	cout << "3 -> hard" << endl;

	int input = -1;

	while ((input != 0) && (input != 1) && (input != 2) && (input != 3)) {
		input = _getch() - 48;
	}
	
	return input;
}

void connect4_operations::run_easy_bot(string(&board)[6][7]) {
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
			column_full = place_piece(ai_player, column, board);
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
			column_full = place_piece(ai_player, column, board);
		} while (column_full);
	}
}

void connect4_operations::easy_computer_game_loop(string (&board)[6][7]) {
	using namespace std::this_thread;
	using namespace std::chrono;
	int input = 0;
	string human_user_name = "";
	bool winner = false;
	bool tie = false;
	int column = 0;
	bool column_exist = false;
	bool column_full = false;
	int ai_drop_column = 0;
	int ai_value = 0;
	player_turn = 1;
	last_ai_x_position = -1;
	last_ai_y_position = -1;

	cout << "Would you like to go first or second (type 1 or 2)?" << endl;
	while ((input != 1) && (input != 2)) {
		input = _getch() - 48;
	}

	human_player = input;
	if (human_player == 1) {
		ai_player = 2;
	}
	else if (human_player == 2) {
		ai_player = 1;
	}

	cout << "Type in your player name." << endl;
	getline(cin >> ws, human_user_name);

	system("CLS");
	while ((winner == false) && (tie == false)) {
		system("CLS");
		print_board(board);

		if (player_turn == human_player) {
			cout << human_user_name + ":\nPlace a piece by typing which column.\n";
			do {
				input = _getch();
				column = input - 48;
				if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
					cout << "Column does not exist.\n" << endl;
					column_exist = false;
				}
				else {
					column_full = place_piece(player_turn, column, board);
					column_exist = true;
				}

			} while (column_full || !column_exist);
		}
		else {
			cout << "Computer:\nPlace a piece by typing which column.\n";
			run_easy_bot(board);
			sleep_for(3500ms);
			place_piece(ai_player, ai_drop_column, board);
		}


		winner = check_winner(player_turn, board);
		if (winner) {
			system("CLS");
			print_board(board);
			if (player_turn == human_player) {
				cout << human_user_name + " won!\n";
			}
			else {
				cout << "Computer won!\n";
			}
		}
		tie = cat_game(board);
		if (tie) {
			system("CLS");
			print_board(board);
			cout << "cat game\n" << endl;
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

void connect4_operations::moderate_computer_game_loop(string(&board)[6][7]) {
	using namespace std::this_thread;
	using namespace std::chrono;
	int input = 0;
	string human_user_name = "";
	bool winner = false;
	bool tie = false;
	int column = 0;
	bool column_exist = false;
	bool column_full = false;
	int ai_drop_column = 0;
	int ai_value = 0;
	int alpha = -2147483647;
	int beta = 2147483647;
	player_turn = 1;
	last_ai_x_position = -1;
	last_ai_y_position = -1;

	cout << "Would you like to go first or second (type 1 or 2)?" << endl;
	while ((input != 1) && (input != 2)) {
		input = _getch() - 48;
	}

	human_player = input;
	if (human_player == 1) {
		ai_player = 2;
	}
	else if (human_player == 2) {
		ai_player = 1;
	}

	cout << "Type in your player name." << endl;
	getline(cin >> ws, human_user_name);

	system("CLS");
	while ((winner == false) && (tie == false)) {
		system("CLS");
		print_board(board);

		if (player_turn == human_player) {
			cout << human_user_name + ":\nPlace a piece by typing which column.\n";
			do {
				input = _getch();
				column = input - 48;
				if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
					cout << "Column does not exist.\n" << endl;
					column_exist = false;
				}
				else {
					column_full = place_piece(player_turn, column, board);
					column_exist = true;
				}

			} while (column_full || !column_exist);
		}
		else {
			cout << "Computer:\nPlace a piece by typing which column.\n";
			minimax(board, ai_drop_column, ai_value, 2, alpha, beta, true);
			sleep_for(3500ms);
			place_piece(ai_player, ai_drop_column, board);
		}


		winner = check_winner(player_turn, board);
		if (winner) {
			system("CLS");
			print_board(board);
			if (player_turn == human_player) {
				cout << human_user_name + " won!\n";
			}
			else {
				cout << "Computer won!\n";
			}
		}
		tie = cat_game(board);
		if (tie) {
			system("CLS");
			print_board(board);
			cout << "cat game\n" << endl;
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}