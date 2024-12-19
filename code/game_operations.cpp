#include "game_operations.h"
#include "io.h"
#include <string>
#include <time.h>
#include <thread>
#include <chrono>

void connect4_operations::initialize_board(std::string (&board)[6][7]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board[i][j] = " . |";
		}
	}
}

void connect4_operations::display_menu(int selection)
{
	display_manager.menu(selection);
}

void connect4_operations::human_game_loop(std::string(&board)[6][7]) {
	std::string p1_username = "";
	std::string p2_username = "";
	bool winner = false;
	bool tie = false;
	bool column_exist = false;
	bool column_full = false;
	int input = 0;
	int column = 0;
	int player_turn = 1;
	
	connect4_io::clear();
	connect4_io::print("Type in your player name, player 1.\n");
	p1_username = connect4_io::getline();
	connect4_io::clear();
	connect4_io::print("Type in your player name, player 2\n");
	p2_username = connect4_io::getline();

	connect4_io::clear();
	while ((winner == false) && (tie == false)) {
		connect4_io::clear();
		display_manager.print_board(board);
		if (player_turn == 1) {
			connect4_io::print(p1_username + ":\nPlace a piece by typing which column.\n");
		}
		else {
			connect4_io::print(p2_username + ":\nPlace a piece by typing which column.\n");
		}

		do {
			
			input = connect4_io::getchar();
			column = input - 48;
			if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
				column_exist = false;
			}
			else {
				column_full = logic_manager.place_piece(player_turn, column, board);
				column_exist = true;
			}

		} while (column_full || !column_exist);

		winner = logic_manager.check_winner(player_turn, board);
		if (winner) {
			connect4_io::clear();
			display_manager.print_board(board);
			if (player_turn == 1) {
				connect4_io::print(p1_username + " won!\n");
			}
			else {
				connect4_io::print(p2_username + " won\n");
			}
		}
		tie = logic_manager.cat_game(board);
		if (tie) {
			connect4_io::clear();
			display_manager.print_board(board);
			connect4_io::print("cat game\n");
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

void connect4_operations::hard_computer_game_loop(std::string(&board)[6][7]) {
	using namespace std::this_thread;
	using namespace std::chrono;
	int input = 0;
	std::string human_user_name = "";
	bool winner = false;
	bool tie = false;
	int column = 0;
	bool column_exist = false;
	bool column_full = false;
	int ai_drop_column = 0;
	int ai_value = 0;
	int alpha = -2147483647;
	int beta = 2147483647;
	int player_turn = 1;
	int ai_player = -1;

	connect4_io::clear();
	connect4_io::print("Would you like to go first or second (type 1 or 2)?\n");
	while ((input != 1) && (input != 2)) {
		input = connect4_io::getchar() - 48;
	}

	int human_player = input;
	if (human_player == 1) {
		ai_player = 2;
	}
	else if (human_player == 2) {
		ai_player = 1;
	}

	logic_manager.set_ai_player(ai_player);
	ai_manager.set_ai_player(ai_player);
	ai_manager.set_human_player(human_player);
	connect4_io::clear();
	connect4_io::print("Type in your player name.\n");
	human_user_name = connect4_io::getline();

	connect4_io::clear();
	while ((winner == false) && (tie == false)) {
		connect4_io::clear();
		display_manager.print_board(board);

		if (player_turn == human_player) {
			connect4_io::print(human_user_name + ":\nPlace a piece by typing which column.\n");
			do {
				input = connect4_io::getchar();
				column = input - 48;
				if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
					column_exist = false;
				}
				else {
					column_full = logic_manager.place_piece(player_turn, column, board);
					column_exist = true;
				}

			} while (column_full || !column_exist);
		}
		else {
			connect4_io::print("Computer:\nPlace a piece by typing which column.\n");
			ai_manager.minimax(board, ai_drop_column, ai_value, 7, alpha, beta, true);
			sleep_for(3500ms);
			logic_manager.place_piece(ai_player, ai_drop_column, board);
		}


		winner = logic_manager.check_winner(player_turn, board);
		if (winner) {
			connect4_io::clear();
			display_manager.print_board(board);
			if (player_turn == human_player) {
				connect4_io::print(human_user_name + " won!\n");
			}
			else {
				connect4_io::print("Computer won!\n");
			}
		}
		tie = logic_manager.cat_game(board);
		if (tie) {
			connect4_io::clear();
			display_manager.print_board(board);
			connect4_io::print("cat game\n");
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

void connect4_operations::easy_computer_game_loop(std::string(&board)[6][7]) {
	using namespace std::this_thread;
	using namespace std::chrono;
	int input = 0;
	std::string human_user_name = "";
	bool winner = false;
	bool tie = false;
	int column = 0;
	bool column_exist = false;
	bool column_full = false;
	int ai_drop_column = 0;
	int player_turn = 1;
	int ai_player = -1;

	connect4_io::clear();
	connect4_io::print("Would you like to go first or second (type 1 or 2)?\n");
	while ((input != 1) && (input != 2)) {
		input = connect4_io::getchar() - 48;
	}

	int human_player = input;
	if (human_player == 1) {
		ai_player = 2;
	}
	else if (human_player == 2) {
		ai_player = 1;
	}

	logic_manager.set_ai_player(ai_player);
	ai_manager.set_ai_player(ai_player);
	ai_manager.set_human_player(human_player);
	connect4_io::clear();
	connect4_io::print("Type in your player name.\n");
	human_user_name = connect4_io::getline();

	connect4_io::clear();
	while ((winner == false) && (tie == false)) {
		connect4_io::clear();
		display_manager.print_board(board);

		if (player_turn == human_player) {
			connect4_io::print(human_user_name + ":\nPlace a piece by typing which column.\n");
			do {
				input = connect4_io::getchar();
				column = input - 48;
				if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
					column_exist = false;
				}
				else {
					column_full = logic_manager.place_piece(player_turn, column, board);
					column_exist = true;
				}

			} while (column_full || !column_exist);
		}
		else {
			connect4_io::print("Computer:\nPlace a piece by typing which column.\n");
			ai_manager.run_easy_bot(board);
			sleep_for(3500ms);
			logic_manager.place_piece(ai_player, ai_drop_column, board);
		}


		winner = logic_manager.check_winner(player_turn, board);
		if (winner) {
			connect4_io::clear();
			display_manager.print_board(board);
			if (player_turn == human_player) {
				connect4_io::print(human_user_name + " won!\n");
			}
			else {
				connect4_io::print("Computer won!\n");
			}
		}
		tie = logic_manager.cat_game(board);
		if (tie) {
			connect4_io::clear();
			display_manager.print_board(board);
			connect4_io::print("cat game\n");
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

void connect4_operations::moderate_computer_game_loop(std::string(&board)[6][7]) {
	using namespace std::this_thread;
	using namespace std::chrono;
	int input = 0;
	std::string human_user_name = "";
	bool winner = false;
	bool tie = false;
	int column = 0;
	bool column_exist = false;
	bool column_full = false;
	int ai_drop_column = 0;
	int ai_value = 0;
	int alpha = -2147483647;
	int beta = 2147483647;
	int player_turn = 1;
	int ai_player = -1;

	connect4_io::clear();
	connect4_io::print("Would you like to go first or second (type 1 or 2)?\n");
	while ((input != 1) && (input != 2)) {
		input = connect4_io::getchar() - 48;
	}

	int human_player = input;
	if (human_player == 1) {
		ai_player = 2;
	}
	else if (human_player == 2) {
		ai_player = 1;
	}

	logic_manager.set_ai_player(ai_player);
	ai_manager.set_ai_player(ai_player);
	ai_manager.set_human_player(human_player);
	connect4_io::clear();
	connect4_io::print("Type in your player name.\n");
	human_user_name = connect4_io::getline();

	connect4_io::clear();
	while ((winner == false) && (tie == false)) {
		connect4_io::clear();
		display_manager.print_board(board);

		if (player_turn == human_player) {
			connect4_io::print(human_user_name + ":\nPlace a piece by typing which column.\n");
			do {
				input = connect4_io::getchar();
				column = input - 48;
				if ((column != 1) && (column != 2) && (column != 3) && (column != 4) && (column != 5) && (column != 6) && (column != 7)) {
					column_exist = false;
				}
				else {
					column_full = logic_manager.place_piece(player_turn, column, board);
					column_exist = true;
				}

			} while (column_full || !column_exist);
		}
		else {
			connect4_io::print("Computer:\nPlace a piece by typing which column.\n");
			ai_manager.minimax(board, ai_drop_column, ai_value, 2, alpha, beta, true);
			sleep_for(3500ms);
			logic_manager.place_piece(ai_player, ai_drop_column, board);
		}


		winner = logic_manager.check_winner(player_turn, board);
		if (winner) {
			connect4_io::clear();
			display_manager.print_board(board);
			if (player_turn == human_player) {
				connect4_io::print(human_user_name + " won!\n");
			}
			else {
				connect4_io::print("Computer won!\n");
			}
		}
		tie = logic_manager.cat_game(board);
		if (tie) {
			connect4_io::clear();
			display_manager.print_board(board);
			connect4_io::print("cat game\n");
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}