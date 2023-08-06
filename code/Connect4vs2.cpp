// Connect4vs2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game_operations.h"
#include <string>
#include "io.h"

int main()
{
    string play_more = "";
    string board[6][7];
    connect4_operations game_manager;
    int game_mode = -1;

    while (play_more != "n") {
        game_manager.initialize_board(board);
        game_mode = game_manager.menu();
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
    
}
