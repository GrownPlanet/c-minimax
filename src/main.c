#include <stdbool.h>
#include <stdio.h>

#include "minimax.h"

int main() {
    printf("123\n");
    printf("456\n");
    printf("789\n");

    bool beginningPlayer = true;

    while (true) {
        Game game = {".........", beginningPlayer};
        bool running = true;

        GAME_printBoard(&game);

        while (running) {
            Result result = GAME_getResult(&game);
            switch (result) {
                case RESULT_undefined:
                    break;
                case RESULT_draw:
                    running = false;
                    printf("Draw!\n");
                    break;
                case RESULT_x_wins:
                    running = false;
                    printf("X wins!\n");
                    break;
                case RESULT_o_wins:
                    running = false;
                    printf("O wins!\n");
                    break;
            }
            if (!running) {
                break;
            }

            if (game.turn) {
                int loc = GAME_getInputNum(&game);
                game.board[loc] = 'x';
            } else {
                int loc = GAME_findBestMove(&game, 'o');
                game.board[loc] = 'o';

                GAME_printBoard(&game);
            }

            game.turn = !game.turn;
        }

        beginningPlayer = !beginningPlayer;
    }
}
