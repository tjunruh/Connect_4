#pragma once
#include <string>
#include <ascii_board.h>
#include <menu.h>
#include <label.h>
#include <frame.h>
#include <text_box.h>
#include <spacer.h>
#include <controls.h>

class display
{
public:
	display(frame* main_display, frame* multipurpose_display, frame* settings_display, controls* game_controls);
	void display_board(const int (&board_data)[6][7], int last_ai_row = -1, int last_ai_column = -1);
	void set_board_directions_content(const std::string& content);
	std::string get_player_username(const std::string& prompt);
	int get_player_order();
	void display_set_controls();

private:
	std::vector<format_tools::index_format> build_central_element_color_structure(int color, bool bold);
	std::vector<format_tools::index_format> build_outside_element_color_structure(int color, bool bold);
	void reset_color(std::string control_name, int color_code);

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

	label settings_label;
	menu settings_menu;
	frame* settings_frame;

	controls* _game_controls;

	enum setting_type
	{
		regular,
		boolean,
		color
	};

	struct control_settings_menu_item
	{
		std::string name_id = "";
		setting_type type = regular;
	};

	enum color_type
	{
		central,
		outside
	};

	const std::vector<control_settings_menu_item> control_settings_menu_items =
	{
		{"up", regular},
		{"down", regular},
		{"right", regular},
		{"left", regular},
		{"select", regular},
		{"quit", regular},
		{"delete", regular},
		{"help", regular},
		{"enable line drawing", boolean},
		{"enable color", boolean},
		{"background color", color},
		{"foreground color", color},
		{"x color", color},
		{"o color", color},
		{"mark color", color},
		{"bold foreground", boolean}
	};

	struct config_name_color_pair
	{
		std::string name_id = "";
		std::string value = "";
		color_type type = central;
	};

	struct config_color_group
	{
		std::string color = "";
		std::vector<config_name_color_pair> groups;
	};

	std::vector<config_color_group> color_group_map
	{
		{"x color", {{"x", "*1*", central}}},
		{"o color", {{"o", "*2*", central}}},
		{"mark color", {{"mark", "*3*", outside}}}
	};
};