typedef struct {
  char board[9];
  bool turn;
} Game;

typedef enum {
  RESULT_undefined,
  RESULT_draw,
  RESULT_x_wins,
  RESULT_o_wins,
} Result;

void GAME_printBoard(Game* game);

int GAME_getInputNum(Game* game);

Result GAME_getResult(Game* game);

int GAME_findBestMove(Game* game, char turn);
