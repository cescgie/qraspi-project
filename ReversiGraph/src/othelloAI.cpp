#include "game.hpp"

void initializeGame(int choice, othelloGame &game,
        bool &blackComputer, bool &whiteComputer, float &timeLimit);

int main(int argc, char *argv[]){
    double duration, starttime, endtime;
    MPI_Init(NULL, NULL);
    starttime = MPI_Wtime();
    //get processor name
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    printf("_____Size: %d | PName: %s| Rank: %d\n",world_size, processor_name, world_rank);
    
    // double wtime, estimate;
    // wtime = omp_get_wtime ( );
    // std::cout << "\n";
    // std::cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n" << std::endl;
    // std::cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n" << std::endl;

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
        // game.board.displayBoard(-1);
        // game.board.displayLegalMoves();
        game.move(-1);

        game.checkGameOver();
    }

    //while (!game.passes[0] && !game.passes[1]) {
    while (!game.gameOver) {
        game.board.findLegalMoves(1, &game.board.moves);
        // game.board.displayBoard(1);
        // game.board.displayLegalMoves();
        game.move(1);
        game.checkGameOver();

        if (game.gameOver) {
            break;
        }

        game.board.findLegalMoves(-1, &game.board.moves);
        // game.board.displayBoard(-1);
        // game.board.displayLegalMoves();
        game.move(-1);
        game.checkGameOver();
    }

    if (world_rank == 0)
    {
        printf("Global time %g\n", MPI_Wtime() - starttime);
    }

    MPI_Finalize();
    // // wtime = omp_get_wtime ( ) - wtime;
    // printf("Global time %g\n", wtime);

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