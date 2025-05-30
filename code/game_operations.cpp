#include "game_operations.h"
#include <string>
#include <time.h>
#include <thread>
#include <chrono>
#include <ascii_io.h>

game_operations::game_operations(frame* main_display, frame* multipurpose_display, frame* settings_frame, controls* game_controls) : display_manager(main_display, multipurpose_display, settings_frame, game_controls)
{
	_game_controls = game_controls;
}

void game_operations::initialize_board(int (&board_data)[6][7]) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			board_data[i][j] = 0;
		}
	}
}

void game_operations::human_game_loop(int (&board_data)[6][7]) {
	std::string p1_username = "";
	std::string p2_username = "";
	bool winner = false;
	bool tie = false;
	bool column_exist = false;
	bool column_full = false;
	int column = 0;
	int player_turn = 1;
	
	p1_username = display_manager.get_player_username("Type in your player name, player 1.");
	p2_username = display_manager.get_player_username("Type in your player name, player 2.");

	while ((winner == false) && (tie == false)) {
		if (player_turn == 1) {
			display_manager.set_board_directions_content(p1_username + ":\nPlace a piece by typing which column.");
		}
		else {
			display_manager.set_board_directions_content(p2_username + ":\nPlace a piece by typing which column.");
		}
		display_manager.display_board(board_data);
		do {
			
			column = ascii_io::getchar();
			if ((column == ascii_io::one) || (column == ascii_io::two) || (column == ascii_io::three) || (column == ascii_io::four) || (column == ascii_io::five) || (column == ascii_io::six) || (column == ascii_io::seven)) {
				column_full = logic_manager.place_piece(player_turn, column - 48, board_data);
				column_exist = true;
			}
			else if (column == _game_controls->get_key("help"))
			{
				display_manager.display_set_controls();
				display_manager.display_board(board_data, logic_manager.get_last_ai_row(), logic_manager.get_last_ai_column());
				column_exist = false;
			}
			else 
			{
				column_exist = false;
			}

		} while (column_full || !column_exist);

		winner = logic_manager.check_winner(player_turn, board_data);
		if (winner) {
			if (player_turn == 1) {
				display_manager.set_board_directions_content(p1_username + " won!");
			}
			else {
				display_manager.set_board_directions_content(p2_username + " won!");
			}
			display_manager.display_board(board_data);
			ascii_io::getchar();
		}
		tie = logic_manager.cat_game(board_data);
		if (tie && !winner) {
			display_manager.set_board_directions_content("cat game");
			display_manager.display_board(board_data);
			ascii_io::getchar();
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}

void game_operations::computer_game_loop(int(&board_data)[6][7], computer_level level)
{
	using namespace std::this_thread;
	using namespace std::chrono;
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
	int human_player = -1;

	logic_manager.reset_last_ai_position();
	int human_player_turn = display_manager.get_player_order();
	if (human_player_turn == ascii_io::one) {
		human_player = 1;
		ai_player = 2;
	}
	else if (human_player_turn == ascii_io::two) {
		ai_player = 1;
		human_player = 2;
	}

	logic_manager.set_ai_player(ai_player);
	ai_manager.set_ai_player(ai_player);
	ai_manager.set_human_player(human_player);

	human_user_name = display_manager.get_player_username("Type in your player name.");

	while ((winner == false) && (tie == false)) {

		if (player_turn == human_player) {
			display_manager.set_board_directions_content(human_user_name + ":\nPlace a piece by typing which column.");
			display_manager.display_board(board_data, logic_manager.get_last_ai_row(), logic_manager.get_last_ai_column());
			do {
				column = ascii_io::getchar();
				if ((column == ascii_io::one) || (column == ascii_io::two) || (column == ascii_io::three) || (column == ascii_io::four) || (column == ascii_io::five) || (column == ascii_io::six) || (column == ascii_io::seven)) {
					column_full = logic_manager.place_piece(player_turn, column - 48, board_data);
					column_exist = true;
				}
				else if (column == _game_controls->get_key("help"))
				{
					display_manager.display_set_controls();
					display_manager.display_board(board_data, logic_manager.get_last_ai_row(), logic_manager.get_last_ai_column());
					column_exist = false;
				}
				else 
				{
					column_exist = false;
				}

			} while (column_full || !column_exist);
		}
		else {
			display_manager.set_board_directions_content("Computer:\nPlace a piece by typing which column.");
			display_manager.display_board(board_data, logic_manager.get_last_ai_row(), logic_manager.get_last_ai_column());
			if (level == easy)
			{
				ai_manager.run_easy_bot(board_data, ai_drop_column);
			}
			else if (level == medium)
			{
				ai_manager.minimax(board_data, ai_drop_column, ai_value, 5, alpha, beta, true);
			}
			else if (level == hard)
			{
				ai_manager.minimax(board_data, ai_drop_column, ai_value, 10, alpha, beta, true);
			}
			sleep_for(3500ms);
			logic_manager.place_piece(ai_player, ai_drop_column, board_data);
		}


		winner = logic_manager.check_winner(player_turn, board_data);
		if (winner) {
			if (player_turn == human_player) {
				display_manager.set_board_directions_content(human_user_name + " won!");
			}
			else {
				display_manager.set_board_directions_content("Computer won!");
			}
			display_manager.display_board(board_data, logic_manager.get_last_ai_row(), logic_manager.get_last_ai_column());
			ascii_io::getchar();
		}
		tie = logic_manager.cat_game(board_data);
		if (tie && !winner) {
			display_manager.set_board_directions_content("cat game");
			display_manager.display_board(board_data, logic_manager.get_last_ai_row(), logic_manager.get_last_ai_column());
			ascii_io::getchar();
		}

		if (player_turn == 1) {
			player_turn = 2;
		}
		else {
			player_turn = 1;
		}
	}
}