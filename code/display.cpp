#include "display.h"
#include <ascii_io.h>

display::display(frame* main_display, frame* multipurpose_display) :
	multipurpose_label(multipurpose_display),
	left_multipurpose_spacer(multipurpose_display, 1, "new line"),
	multipurpose_text_box(multipurpose_display, "none", 3),
	right_multipurpose_spacer(multipurpose_display, 1),
	board(main_display, "board_configs/connect_4_board.txt", "default"),
	left_main_spacer(main_display, 1, "new line"),
	directions_label(main_display),
	right_main_spacer(main_display, 1)
{
	main_frame = main_display;
	multipurpose_frame = multipurpose_display;
	board.load_configuration("board_configs/x_piece.txt", "x", -1, -1, '*');
	board.load_configuration("board_configs/o_piece.txt", "o", -1, -1, '*');
	board.load_configuration("board_configs/designate.txt", "mark", -1, -1, '*');
	board.set_alignment("center block");
	board.set_spacing(5, 5, 0, 0);
	directions_label.set_spacing(1, 1, 0, 0);
	directions_label.set_border_spacing(1, 1, 0, 0);
	directions_label.add_border(true);
	main_frame->set_coordinate_width_multiplier(1, 1, 1);

	multipurpose_frame->set_coordinate_width_multiplier(1, 1, 1);
	multipurpose_label.set_alignment("center block");
	multipurpose_label.set_spacing(15, 0, 0, 0);
}

void display::display_board(const int (&board_data)[6][7], int last_ai_row, int last_ai_column) {

	board.clear_all();
	board.start_logging("ascii_board.log");
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

	if (last_ai_row > 0 && last_ai_column > 0)
	{
		board.activate_configuration("mark", last_ai_row, last_ai_column);
	}

	board.stop_logging();
	board.sync();
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