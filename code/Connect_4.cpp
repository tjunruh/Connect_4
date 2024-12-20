#include "game_operations.h"
#include <string>
#include <frame.h>
#include <menu.h>
#include <label.h>
#include <ascii_io.h>

#ifdef __linux__
#include <unistd.h>
#include <ncurses.h>
#endif

int main()
{
#ifdef __linux__
    ascii_io::ncurses_init();
#endif
    std::string play_more = "";
    int board[6][7];
    frame* home_frame = new frame();
    frame* main_frame = new frame();
    frame* multipurpose_frame = new frame();
    game_operations game_manager(main_frame, multipurpose_frame);
    label logo(home_frame);
    menu initialization_menu(home_frame, "new line");
    logo.set_alignment("center block");
    logo.set_output(game_manager.logo);
    logo.set_spacing(15, 3, 0, 0);

    initialization_menu.append_item("Multiplayer");
    initialization_menu.append_item("Easy Computer");
    initialization_menu.append_item("Moderate Computer");
    initialization_menu.append_item("Hard Computer");
    initialization_menu.append_item("Exit");
    initialization_menu.disable_quit();
    initialization_menu.set_alignment("center block");
    ascii_io::hide_cursor();

    do {
        home_frame->display();
        std::string selection = "";
        int key_stroke = ascii_io::undefined;
        initialization_menu.get_selection(selection, key_stroke);
        game_manager.initialize_board(board);

        if (selection == "Multiplayer") {
            game_manager.human_game_loop(board);
        }
        else if (selection == "Easy Computer") {
            game_manager.easy_computer_game_loop(board);
        }
        else if (selection == "Moderate Computer") {
            game_manager.moderate_computer_game_loop(board);
        }
        else if (selection == "Hard Computer") {
            game_manager.hard_computer_game_loop(board);
        }
        else if (selection == "Exit")
        {
            break;
        }
    } while (1);

    delete(main_frame);
    delete(multipurpose_frame);
    
#ifdef __linux__
    ascii_io::ncurses_end();
#endif
}
