#pragma once
#include <string>

class logic
{
public:
	void set_ai_player(int player);
	bool check_winner(int player, const int (&board_data)[6][7]);
	bool cat_game(const int (&board_data)[6][7]);
	bool place_piece(int player, int column, int (&board_data)[6][7]);
	int get_last_ai_row();
	int get_last_ai_column();
	void reset_last_ai_position();
private:
	int ai_player = -1;
	int last_ai_row = -1;
	int last_ai_column = -1;

	bool rows_check_winner(int player, const int (&board_data)[6][7]);
	bool columns_check_winner(int player, const int (&board_data)[6][7]);
	bool diagonal_top_left_triangle_check_winner(int player, const int (&board_data)[6][7]);
	bool diagonal_bottom_left_triangle_check_winner(int player, const int (&board_data)[6][7]);
	bool diagonal_top_right_triangle_check_winner(int player, const int (&board_data)[6][7]);
	bool diagonal_bottom_right_triangle_check_winner(int player,  const int (&board_data)[6][7]);
	bool diagonal_check_winner(int player, const int (&board_data)[6][7]);
};