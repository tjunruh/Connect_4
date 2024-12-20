#pragma once
#include <string>
#include <ascii_board.h>
#include <menu.h>
#include <label.h>
#include <frame.h>
#include <text_box.h>
#include <spacer.h>

class display
{
public:
	display(frame* main_display, frame* multipurpose_display);
	void display_board(const int (&board_data)[6][7], int last_ai_row = -1, int last_ai_column = -1);
	void set_board_directions_content(const std::string& content);
	std::string get_player_username(const std::string& prompt);
	int get_player_order();

private:

	label multipurpose_label;
	spacer left_multipurpose_spacer;
	text_box multipurpose_text_box;
	spacer right_multipurpose_spacer;
	frame* multipurpose_frame;

	ascii_board board;
	spacer left_main_spacer;
	label directions_label;
	spacer right_main_spacer;
	frame* main_frame;
};