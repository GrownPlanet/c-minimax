#include <stdbool.h>
#include <stdio.h>
#include <limits.h>

#include "minimax.h"

typedef enum {
    RESULT_FOR_undefined,
    RESULT_FOR_win,
} ResultFor;

void GAME_printBoard(Game* game) {
    char buf[12];
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            int buf_index = i * 4 + k;
            int game_index = i * 3 + k;
            buf[buf_index] = game->board[game_index];
        }
        buf[i * 4 + 3] = '\n';
    }
    printf("%s", buf);
}

int GAME_getInputNum(Game* game) {
    int input;

    while (true) {
        printf("move: ");
        scanf("%d", &input);

        if (
            input > 9 ||
            input < 1 ||
            game->board[input - 1] != '.'
        ) {
            printf("invalid input, please give a number between 1 and 9\n");
        } else {
            return input - 1;
        }
    }
}

ResultFor getResultFor(Game* game, char ch) {
    for (int i = 0; i < 3; i++) {
        int k = i * 3;
        if (game->board[k] == ch && game->board[k + 1] == ch && game->board[k + 2] == ch) {
            return RESULT_FOR_win;
        }
        if (game->board[i] == ch && game->board[i + 3] == ch && game->board[i + 6] == ch) {
            return RESULT_FOR_win;
        }
    }
    if (game->board[0] == ch && game->board[4] == ch && game->board[8] == ch) {
        return RESULT_FOR_win;
    }
    if (game->board[2] == ch && game->board[4] == ch && game->board[6] == ch) {
        return RESULT_FOR_win;
    }
    return RESULT_FOR_undefined;
}

Result GAME_getResult(Game* game) {
    ResultFor o_wins = getResultFor(game, 'o');
    if (o_wins == RESULT_FOR_win) {
        return RESULT_o_wins;
    }

    ResultFor x_wins = getResultFor(game, 'x');
    if (x_wins == RESULT_FOR_win) {
        return RESULT_x_wins;
    }

    bool draw = true;
    for (int i = 0; i < 9; i++) {
        if (game->board[i] == '.') {
            draw = false;
            break;
        }
    }
    if (draw) {
        return RESULT_draw;
    }

    return RESULT_undefined;
}

int minimax(Game* game, char turn) {
    Result result = GAME_getResult(game);

    switch (result) {
        case RESULT_x_wins:
            return 1;
        case RESULT_draw:
            return 0;
        case RESULT_o_wins:
            return -1;
        default:
            break;
    }

    bool max = (turn == 'x');
    int bestResult = max ? INT_MIN : INT_MAX;
    char nextTurn = max ? 'o' : 'x';

    for (int i = 0; i < 9; i++) {
        if (game->board[i] == '.') {
            game->board[i] = turn;
            int result = minimax(game, nextTurn);

            if (max && result > bestResult) {
                bestResult = result;
            } 
            else if (!max && result < bestResult) {
                bestResult = result;
            }

            game->board[i] = '.';
        }
    }

    return bestResult;
}

int GAME_findBestMove(Game* game, char turn) {
    bool max = turn == 'x';
    int bestResult = max ? INT_MIN : INT_MAX;
    int bestResultLoc;
    char nextTurn = max ? 'o' : 'x';

    for (int i = 0; i < 9; i++) {
        if (game->board[i] == '.') {
            game->board[i] = turn;

            int result = minimax(game, nextTurn);

            if (max && result > bestResult) {
                bestResult = result;
                bestResultLoc = i;
            } 
            else if (!max && result < bestResult) {
                bestResult = result;
                bestResultLoc = i;
            }
            game->board[i] = '.';
        }
    }

    return bestResultLoc;
}
