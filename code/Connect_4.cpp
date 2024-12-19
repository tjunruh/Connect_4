// Connect4vs2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game_operations.h"
#include <string>
#include "io.h"
#ifdef __linux__
#include <unistd.h>
#include <ncurses.h>
#endif

int main()
{
#ifdef __linux__
    initscr();
    raw();
    noecho();
    cbreak();
#endif
    std::string play_more = "";
    std::string board[6][7];
    connect4_operations game_manager;
    int game_mode = -1;
    int selection = 0;

    while (play_more != "n") {
        selection = 0;
        game_manager.initialize_board(board);
        int input = -1;
        do {
            connect4_io::clear();
            game_manager.display_menu(selection);
            input = connect4_io::getchar();
            if ((input == UP) && (selection != 0)) {
                selection--;
            }
            else if ((input == DOWN) && (selection != 3)) {
                selection++;
            }
        } while (input != ENTER);

        game_mode = selection;

        if (game_mode == 0) {
            game_manager.human_game_loop(board);
        }
        else if (game_mode == 1) {
            game_manager.easy_computer_game_loop(board);
        }
        else if (game_mode == 2) {
            game_manager.moderate_computer_game_loop(board);
        }
        else if (game_mode == 3) {
            game_manager.hard_computer_game_loop(board);
        }

        play_more = "";
        connect4_io::print("Play again?\ntype y or n.\n");
        while ((play_more != "y") && (play_more != "n")) {
            play_more = connect4_io::getline();
        }
    }
    
#ifdef __linux__
    endwin();
#endif
}
