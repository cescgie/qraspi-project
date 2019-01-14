#include "game.hpp"

void initializeGame(int choice, othelloGame &game,
        bool &blackComputer, bool &whiteComputer, float &timeLimit);

int main(int argc, char *argv[]){
    othelloBoard board;
    othelloGame game;
    bool blackComputer = false, whiteComputer = false;
    float timeLimit = 0.0;

    if (world_rank == 0)
    {
        initializeGame(1, game, blackComputer, whiteComputer, timeLimit);
    }

    // Play game
    if (game.toMove == -1) {
        game.board.findLegalMoves(-1, &game.board.moves);
        game.board.displayBoard(-1);
        game.board.displayLegalMoves();
        game.move(-1);

        game.checkGameOver();
    }

    //while (!game.passes[0] && !game.passes[1]) {
    while (!game.gameOver) {
        game.board.findLegalMoves(1, &game.board.moves);
        game.board.displayBoard(1);
        game.board.displayLegalMoves();
        game.move(1);
        game.checkGameOver();

        if (game.gameOver) {
            break;
        }

        game.board.findLegalMoves(-1, &game.board.moves);
        game.board.displayBoard(-1);
        game.board.displayLegalMoves();
        game.move(-1);
        game.checkGameOver();
    }

    return 0;
}

// Initialize game appropriately
void initializeGame(int choice, othelloGame &game,
    bool &blackComputer, bool &whiteComputer, float &timeLimit) {
    blackComputer = true;
    whiteComputer = true;

    if (blackComputer || whiteComputer) {
        timeLimit = 1;
    }

    game.newGame(blackComputer, whiteComputer, timeLimit);
}