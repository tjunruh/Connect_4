#include "display.h"
#include <ascii_io.h>
#include "file_management.h"

display::display(frame* main_display, frame* multipurpose_display, frame* settings_display, controls* game_controls) :
	multipurpose_label(multipurpose_display),
	multipurpose_text_box(multipurpose_display, "new line", 3),
	board(main_display, "board_configs/connect_4_board.txt", "default", "none"),
	directions_label(main_display, "new line"),
	settings_label(settings_display),
	settings_menu(settings_display, "new line")
{
	_game_controls = game_controls;
	main_frame = main_display;
	multipurpose_frame = multipurpose_display;
	bool bold = game_controls->get_key("bold foreground");
	std::string x_piece_value = board.load_configuration("board_configs/x_piece.txt");
	std::string o_piece_value = board.load_configuration("board_configs/o_piece.txt");
	std::string mark_piece_value = board.load_configuration("board_configs/designate.txt");

	std::vector<config_color_group> color_group_map
	{
		{"x color", {{"x", x_piece_value}}},
		{"o color", {{"o", o_piece_value}}},
		{"mark color", {{"mark", mark_piece_value}}}
	};

	board.add_configuration("x", -1, -1, x_piece_value, '*', format_tools::build_color_for_value(x_piece_value, '*', _game_controls->get_key("x color"), format_tools::none, bold));
	board.add_configuration("o", -1, -1, o_piece_value, '*', format_tools::build_color_for_value(o_piece_value, '*', _game_controls->get_key("o color"), format_tools::none, bold));
	board.add_configuration("mark", -1, -1, mark_piece_value, '*', format_tools::build_color_for_value(mark_piece_value, '*', _game_controls->get_key("mark color"), format_tools::none, bold));
	board.set_alignment("center block");
	board.set_spacing(5, 5, 0, 0);
	directions_label.set_spacing(1, 1, 0, 0);
	directions_label.set_border_spacing(1, 1, 0, 0);
	directions_label.add_border(true);
	directions_label.use_spacing_width_multipliers(true);
	directions_label.set_width_multiplier(1.0);
	directions_label.set_spacing_width_multipliers(1.0, 1.0);
	main_frame->enable_color(_game_controls->get_key("enable color"));
	main_frame->enable_dec(_game_controls->get_key("enable line drawing"));
	main_frame->set_dec_format_characters('=', '|', '+', '.');
	main_frame->set_default_foreground_color(_game_controls->get_key("foreground color"));
	main_frame->set_default_background_color(_game_controls->get_key("background color"));

	multipurpose_label.set_alignment("center block");
	multipurpose_label.set_spacing(15, 0, 0, 0);
	multipurpose_text_box.use_spacing_width_multipliers(true);
	multipurpose_text_box.set_width_multiplier(1.0);
	multipurpose_text_box.set_spacing_width_multipliers(1.0, 1.0);
	multipurpose_frame->enable_color("enable color");
	multipurpose_frame->enable_dec(_game_controls->get_key("enable line drawing"));
	multipurpose_frame->set_default_foreground_color(_game_controls->get_key("foreground color"));
	multipurpose_frame->set_default_background_color(_game_controls->get_key("background color"));

	settings_frame = settings_display;
	settings_label.set_alignment("center");
	settings_label.set_output("Settings Menu");
	settings_menu.enable_quit();
	settings_menu.separate_items(true);
	settings_menu.set_alignment("center");
	settings_menu.add_border(true);
	settings_frame->enable_color(_game_controls->get_key("enable color"));
	settings_frame->enable_dec(_game_controls->get_key("enable line drawing"));
	settings_frame->set_default_foreground_color(_game_controls->get_key("foreground color"));
	settings_frame->set_default_background_color(_game_controls->get_key("background color"));

	color_group_map[0].groups[0].value = board.load_configuration("board_configs/x_piece.txt");
	color_group_map[1].groups[0].value = board.load_configuration("board_configs/o_piece.txt");
	color_group_map[2].groups[0].value = board.load_configuration("board_configs/designate.txt");

	initialize_settings_menu();
}

void display::display_board(const int (&board_data)[6][7], int last_ai_row, int last_ai_column) {

	board.clear_all();
	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int j = 0; j < 7; j++)
		{
			if (board_data[i][j] == 1)
			{
				board.activate_configuration("x", i, j);
			}
			else if (board_data[i][j] == 2)
			{
				board.activate_configuration("o", i, j);
			}
		}
	}

	if (last_ai_row >= 0 && last_ai_column >= 0)
	{
		board.activate_configuration("mark", last_ai_row, last_ai_column);
	}

	board.build();
	main_frame->display();
}

void display::set_board_directions_content(const std::string& content)
{
	directions_label.set_output(content);
}

std::string display::get_player_username(const std::string& prompt)
{
	int input = ascii_io::undefined;
	multipurpose_label.set_output(prompt);
	multipurpose_text_box.add_border(true);
	multipurpose_frame->display();
	do
	{
		input = multipurpose_text_box.write();
	} while (input != ascii_io::enter);
	std::string written_content = multipurpose_text_box.get_text();
	ascii_io::hide_cursor();
	multipurpose_text_box.clear();
	return written_content;
}

int display::get_player_order()
{
	int input = ascii_io::undefined;
	multipurpose_label.set_output("Would you like to go first or second (type 1 or 2)?");
	multipurpose_text_box.add_border(false);
	multipurpose_frame->display();
	do
	{
		input = ascii_io::getchar();
	} while ((input != ascii_io::one) && (input != ascii_io::two));
	return input;
}

void display::reset_color(std::string control_name, int color_code)
{
	for (unsigned int i = 0; i < color_group_map.size(); i++)
	{
		if (color_group_map[i].color == control_name)
		{
			for (unsigned int j = 0; j < color_group_map[i].groups.size(); j++)
			{
				std::vector<format_tools::index_format> color;
				color = format_tools::build_color_for_value(color_group_map[i].groups[j].value, '*', color_code, format_tools::none, _game_controls->get_key("bold foreground"));
				board.set_sub_configuration_color(color_group_map[i].groups[j].name_id, color_group_map[i].groups[j].value, color);
			}
		}
	}
}

void display::initialize_settings_menu()
{
	settings_menu.set_lines_count(-4);
	for (unsigned int i = 0; i < control_settings_menu_items.size(); i++)
	{
		settings_menu.append_item(control_settings_menu_items[i].name_id);
		std::string label_name;
		if (control_settings_menu_items[i].type == regular)
		{
			label_name = ascii_io::get_key_name(_game_controls->get_key(control_settings_menu_items[i].name_id));
		}
		else if (control_settings_menu_items[i].type == color)
		{
			label_name = format_tools::get_color_name(_game_controls->get_key(control_settings_menu_items[i].name_id));
		}
		else if (control_settings_menu_items[i].type == boolean)
		{
			if (_game_controls->get_key(control_settings_menu_items[i].name_id) == 0)
			{
				label_name = "No";
			}
			else if (_game_controls->get_key(control_settings_menu_items[i].name_id) == 1)
			{
				label_name = "Yes";
			}
		}
		settings_menu.set_item_label(control_settings_menu_items[i].name_id, label_name);
	}
}

void display::display_set_controls()
{
	std::vector<int> menu_select_buttons;
	menu_select_buttons.push_back(_game_controls->get_key("select"));
	settings_menu.set_controls(menu_select_buttons, _game_controls->get_key("up"), _game_controls->get_key("down"), _game_controls->get_key("quit"));

	settings_frame->enable_dec(_game_controls->get_key("enable line drawing"));

	if (_game_controls->get_key("enable color"))
	{
		settings_frame->set_default_background_color(_game_controls->get_key("background color"));
		settings_frame->set_default_foreground_color(_game_controls->get_key("foreground color"));
	}

	settings_menu.build();
	settings_frame->display();
	std::string selection = "";
	int key_stroke = ascii_io::undefined;
	do
	{
		settings_menu.get_selection(selection, key_stroke);
		settings_menu.build();
		for (unsigned int i = 0; i < control_settings_menu_items.size(); i++)
		{
			if (selection == control_settings_menu_items[i].name_id)
			{
				if (control_settings_menu_items[i].type == regular)
				{
					settings_label.set_output("Press key to bind to " + selection);
					settings_label.refresh();
					int key = ascii_io::getchar();
					_game_controls->unbind(control_settings_menu_items[i].name_id);
					_game_controls->bind(control_settings_menu_items[i].name_id, key);
					settings_menu.set_item_label(selection, ascii_io::get_key_name(key));
					settings_label.set_output("");
					settings_label.refresh();
				}
				else if (control_settings_menu_items[i].type == color)
				{
					settings_label.set_output("b -> blue, c -> cyan, d -> black, g -> green, m -> magenta, r -> red, w -> white, y -> yellow");
					settings_label.refresh();
					int key = ascii_io::getchar();
					int selected_color = format_tools::none;
					switch (key)
					{
					case ascii_io::b:
						selected_color = format_tools::blue;
						break;
					case ascii_io::c:
						selected_color = format_tools::cyan;
						break;
					case ascii_io::d:
						selected_color = format_tools::black;
						break;
					case ascii_io::g:
						selected_color = format_tools::green;
						break;
					case ascii_io::m:
						selected_color = format_tools::magenta;
						break;
					case ascii_io::r:
						selected_color = format_tools::red;
						break;
					case ascii_io::w:
						selected_color = format_tools::white;
						break;
					case ascii_io::y:
						selected_color = format_tools::yellow;
						break;
					}
					_game_controls->unbind(control_settings_menu_items[i].name_id);
					_game_controls->bind(control_settings_menu_items[i].name_id, selected_color);
					reset_color(control_settings_menu_items[i].name_id, selected_color);
					settings_menu.set_item_label(selection, format_tools::get_color_name(selected_color));
					settings_label.set_output("");
					settings_label.refresh();
				}
				else if (control_settings_menu_items[i].type == boolean)
				{
					bool value = _game_controls->get_key(control_settings_menu_items[i].name_id);
					value = !value;
					_game_controls->unbind(control_settings_menu_items[i].name_id);
					_game_controls->bind(control_settings_menu_items[i].name_id, value);
					std::string label_name = "";
					if (value == 0)
					{
						label_name = "No";
					}
					else if (value == 1)
					{
						label_name = "Yes";
					}
					settings_menu.set_item_label(selection, label_name);
					main_frame->enable_dec(_game_controls->get_key("enable line drawing"));
					multipurpose_frame->enable_dec(_game_controls->get_key("enable line drawing"));
					settings_frame->enable_dec(_game_controls->get_key("enable line drawing"));
					if (control_settings_menu_items[i].name_id == "bold foreground")
					{
						for (unsigned int j = 0; j < color_group_map.size(); j++)
						{
							reset_color(color_group_map[j].color, _game_controls->get_key(color_group_map[j].color));
						}
					}
				}
				settings_menu.build();
				settings_frame->display();
			}
		}
	} while (selection != "");
	connect_4_file_management::save_controls("controls.json", _game_controls);

	main_frame->enable_color(_game_controls->get_key("enable color"));

	if (_game_controls->get_key("enable color"))
	{
		main_frame->set_default_background_color(_game_controls->get_key("background color"));
		main_frame->set_default_foreground_color(_game_controls->get_key("foreground color"));
		multipurpose_frame->set_default_background_color(_game_controls->get_key("background color"));
		multipurpose_frame->set_default_foreground_color(_game_controls->get_key("foreground color"));
	}
}