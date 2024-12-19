#pragma once
#include <string>

class logic
{
public:
	void set_ai_player(int player);
	bool check_winner(int player, std::string board[6][7]);
	bool cat_game(std::string board[6][7]);
	bool place_piece(int player, int column, std::string(&board)[6][7]);

private:
	int ai_player = -1;
	int last_ai_x_position = -1;
	int last_ai_y_position = -1;

	bool rows_check_winner(int player, std::string board[6][7]);
	bool columns_check_winner(int player, std::string board[6][7]);
	bool diagonal_top_left_triangle_check_winner(int player, std::string board[6][7]);
	bool diagonal_bottom_left_triangle_check_winner(int player, std::string board[6][7]);
	bool diagonal_top_right_triangle_check_winner(int player, std::string board[6][7]);
	bool diagonal_bottom_right_triangle_check_winner(int player, std::string board[6][7]);
	bool diagonal_check_winner(int player, std::string board[6][7]);
};