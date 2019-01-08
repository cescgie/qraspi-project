#include "heuristic.hpp"
#include "player.hpp"

// Driver for player's move, regardless of player
std::pair<int, std::list<int>> othelloPlayer::move(othelloBoard &board,
        std::unordered_map<int, std::list<int>> &legalMoves,
        bool &pass, std::string &moveHistory) {

    std::pair<int, std::list<int>> moveChoice;
    if (computer) {
        moveChoice = computerMove(board, legalMoves, pass, moveHistory);
    }
    else {
        moveChoice = humanMove(legalMoves, pass);
    }

    moveHistory.append(std::to_string(moveChoice.first) + ",");

    return moveChoice;
}

// Prompts user for next move
std::pair<int, std::list<int>> othelloPlayer::humanMove(
        std::unordered_map<int, std::list<int>> &legalMoves, bool &pass) {
    std::string str;
    std::pair<int, std::list<int>> move;
    int moveNum = 0;
    int coordIndex = -1;
    bool validInput = false;

    if (legalMoves.empty()) {
        std::cout << "No legal moves!" << std::endl;
        std::cout << "\tEnter any non-empty string to pass: ";
        std::cin >> str;
        while (std::cin.get() != '\n');          // clear buffer
        std::cout << std::endl;
        pass = true;
        return move;
    }

    do {
        std::cout << "\tSelect move number/square coordinate: ";
        std::cin >> str;
        while (std::cin.get() != '\n');          // clear buffer

        coordIndex = coord2index(str);
        std::istringstream iss(str);
        iss >> moveNum;

        if (coordIndex != -1
                && legalMoves.find(coordIndex) != legalMoves.end()) {
            std::cout << std::endl;
            return *legalMoves.find(coordIndex);
        }
        else if (!iss.eof() || moveNum > legalMoves.size() || moveNum < 1) {
            std::cout << "\tInvalid input. Please try again.\n" << std::endl;
        }
        else {
            validInput = true;
            std::cout << std::endl;
        }
    }
    while (!validInput);

    int i = 0;
    for (std::pair<int, std::list<int>> keyval : legalMoves) {
        move = keyval;
        i++;
        if (i == moveNum) {
            break;
        }
    }

    return move;
}

int othelloPlayer::coord2index(std::string coord) {
    if (coord.length() != 2) {
        return -1;
    }

    int index = 0;
    switch(coord.at(0)) {
        case 'A':
        case 'a':
            index = 0;
            break;
        case 'B':
        case 'b':
            index = 1;
            break;
        case 'C':
        case 'c':
            index = 2;
            break;
        case 'D':
        case 'd':
            index = 3;
            break;
        case 'E':
        case 'e':
            index = 4;
            break;
        case 'F':
        case 'f':
            index = 5;
            break;
        case 'G':
        case 'g':
            index = 6;
            break;
        case 'H':
        case 'h':
            index = 7;
            break;
        default:
            return -1;
    }

    switch(coord.at(1)) {
        case '1':
            index += 0;
            break;
        case '2':
            index += 8;
            break;
        case '3':
            index += 16;
            break;
        case '4':
            index += 24;
            break;
        case '5':
            index += 32;
            break;
        case '6':
            index += 40;
            break;
        case '7':
            index += 48;
            break;
        case '8':
            index += 56;
            break;
        default:
            return -1;
    }

    return index;
}

// Driver for the AI algorithm
std::pair<int, std::list<int>> othelloPlayer::computerMove(othelloBoard &board,
        std::unordered_map<int, std::list<int>> &legalMoves, bool &pass,
        std::string &moveHistory) {
    std::chrono::time_point<std::chrono::system_clock> startTime
        = startTimer();
    std::pair<int, std::list<int>> move;
    std::pair<int, std::list<int>> bestMove;
    std::unordered_map<std::string, int>::iterator query
        = database.openingBook.find(moveHistory);

    if (legalMoves.empty()) {
        std::cout << "No legal moves!" << std::endl;
        std::cout << "\tComputer passes.\n" << std::endl;
        pass = true;
        return bestMove;
    }
    else if (legalMoves.size() == 1) {
        std::cout << "Only one legal move!" << std::endl;
        std::cout << "\tComputer takes only legal move." << std::endl;
        bestMove = *legalMoves.begin();
    }
    else if (query != database.openingBook.end()) {
        std::cout << "Known opening!" << std::endl;
        std::cout << "\tComputer takes next move from opening book."
            << std::endl;
        bestMove = *legalMoves.find(query->second);
    }
    else {
        int maxDepth = 64 - board.discsOnBoard;
        std::cout << "\tmaxDepth " << maxDepth << std::endl;
        std::cout << "\tdiscsOnBoard " << board.discsOnBoard << std::endl;

        //get processor name
        char processor_name[MPI_MAX_PROCESSOR_NAME];
        int name_len;
        MPI_Get_processor_name(processor_name, &name_len);
        int world_rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        printf("_____Size: %d | PName: %s| Rank: %d\n",world_size, processor_name, world_rank);

        if (maxDepth < 10) {
            // Search to terminal states
            std::cout << "Searching remainder of game tree..." << std::endl;
            std::cout << "\tSearching to depth " << maxDepth;

            bestMove = depthLimitedAlphaBeta(board, maxDepth, startTime,
                    board.timeLimit);

            std::cout << "\t\tSearch complete." << std::endl;
        }
        else {
            std::cout << "\n";
            std::cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n" << std::endl;
            std::cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n" << std::endl;

            // Search by iterative deepening
            std::cout << "Searching game tree..." << std::endl;
            
            int depthLimit;
            // #pragma omp parallel for private(depthLimit)
            for (depthLimit = 1; depthLimit <= maxDepth; depthLimit++) {
                std::cout << "\tSearching to depth " << depthLimit;
                // #pragma omp single
                move = depthLimitedAlphaBeta(board, depthLimit, startTime,
                        board.timeLimit);

                if (move.first == -1) {
                    std::cout << "\t\tSearch aborted." << std::endl;
                    break;
                }
                else {
                    std::cout << "\t\tSearch complete." << std::endl;
                    bestMove = move;
                }

                // If time is more than half up, don't bother with next depth
                if (stopTimer(startTime) > 0.5*board.timeLimit) {
                    break;
                }

                // if(move.first != -1 && stopTimer(startTime) < 0.5*board.timeLimit){
                //     std::cout << "\tSearching to depth " << depthLimit;
                //     std::cout << "\t\tSearch complete." << std::endl;
                //     bestMove = move;
                // }
            }
        }
    }

    std::cout << "\tTime elapsed: " << stopTimer(startTime) << " sec"
        << std::endl;

    int rowNum = 0, colNum = 0;
    std::string colCoord = "ABCDEFGH";
    std::string rowCoord = "12345678";
    board.index2coord(bestMove.first, colNum, rowNum);
    std::cout << "\tComputer takes: " << colCoord[colNum] << rowCoord[rowNum]
        << "\n" << std::endl;

    return bestMove;
}

// Returns time point
std::chrono::time_point<std::chrono::system_clock> othelloPlayer::startTimer() {
    return std::chrono::system_clock::now();
}

// Returns time elapsed in seconds
float othelloPlayer::stopTimer(
        std::chrono::time_point<std::chrono::system_clock> startTime) {
    std::chrono::time_point<std::chrono::system_clock> endTime =
        std::chrono::system_clock::now();
    std::chrono::duration<float> elapsedSeconds = endTime - startTime;
    return elapsedSeconds.count();
}

// Performs depth-limited minimax search with alpha-beta pruning
// Implemented iteratively to avoid recursion overhead
// Returns move for square -1 if time runs out
// TODO implement killer move heuristic
std::pair<int, std::list<int>> othelloPlayer::depthLimitedAlphaBeta(
        othelloBoard &board, int depthLimit,
        std::chrono::time_point<std::chrono::system_clock> startTime,
        float timeLimit) {

    // Initialize root node
    nodeStack[0].isMaxNode = true;
    nodeStack[0].alpha = INT_MIN;
    nodeStack[0].beta = INT_MAX;
    nodeStack[0].score = INT_MIN;
    nodeStack[0].board = board;
    nodeStack[0].moveIterator = nodeStack[0].board.moves.begin();
    nodeStack[0].prevIterator = nodeStack[0].moveIterator;
    nodeStack[0].lastMove = nodeStack[0].board.moves.end();

    int depth = 0;
    int leafScore = 0;
    std::unordered_map<int, std::list<int>>::iterator bestMove =
        nodeStack[0].board.moves.begin();

    // While we have not evaluated all the root's children
    while (true) {
        // If we have evaluated all children
        if (nodeStack[depth].moveIterator
                == nodeStack[depth].lastMove) {
            if (depth-- == 0) {
                if (nodeStack[1].score > nodeStack[0].score
                        || (nodeStack[1].score == nodeStack[0].score
                            && rand() % 2 == 0)) {
                    nodeStack[0].score = nodeStack[1].score;
                    bestMove = nodeStack[0].prevIterator;
                }

                if (nodeStack[0].score > nodeStack[0].alpha) {
                    nodeStack[0].alpha = nodeStack[0].score;
                }

                break;
            }

            if (nodeStack[depth].isMaxNode) {
                if (nodeStack[depth+1].score > nodeStack[depth].score
                        || (nodeStack[depth+1].score == nodeStack[depth].score
                            && rand() % 2 == 0)) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                    if (depth == 0) {
                        bestMove = nodeStack[0].prevIterator;
                    }
                }

                if (nodeStack[depth].score > nodeStack[depth].alpha) {
                    nodeStack[depth].alpha = nodeStack[depth].score;
                }
            }
            else {
                if (nodeStack[depth+1].score < nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score;
                }

                if (nodeStack[depth].score < nodeStack[depth].beta) {
                    nodeStack[depth].beta = nodeStack[depth].score;
                }
            }
        }
        // If we can prune
        else if (nodeStack[depth].beta <= nodeStack[depth].alpha) {
            if (depth-- == 0) {
                if (nodeStack[1].score > nodeStack[0].score
                    || (nodeStack[1].score == nodeStack[0].score
                        && rand() % 2 == 0)) {
                    nodeStack[0].score = nodeStack[1].score;
                    bestMove = nodeStack[0].prevIterator;
                }

                if (nodeStack[0].score > nodeStack[0].alpha) {
                    nodeStack[0].alpha = nodeStack[0].score;
                }

                //killerMoves[1][1] = killerMoves[1][0];
                //killerMoves[1][0] = nodeStack[1].prevIterator->first;

                break; // FIXME should it be break or continue here???
            }

            if (nodeStack[depth].isMaxNode) {
                if (nodeStack[depth+1].score > nodeStack[depth].score
                    || (nodeStack[depth+1].score == nodeStack[depth].score
                        && rand() % 2 == 0)) {
                    nodeStack[depth].score = nodeStack[depth+1].score - 1;
                    if (depth == 0) {
                        bestMove = nodeStack[0].prevIterator;
                    }
                }

                if (nodeStack[depth].score > nodeStack[depth].alpha) {
                    nodeStack[depth].alpha = nodeStack[depth].score;
                }

                //killerMoves[depth+1][1] = killerMoves[depth+1][0];
                //killerMoves[depth+1][0] = nodeStack[depth+1].prevIterator->first;
            }
            else {
                if (nodeStack[depth+1].score < nodeStack[depth].score) {
                    nodeStack[depth].score = nodeStack[depth+1].score + 1;
                }

                if (nodeStack[depth].score < nodeStack[depth].beta) {
                    nodeStack[depth].beta = nodeStack[depth].score;
                }
            }
        }
        else {
            // Generate next node, increment iterators
            nodeStack[depth+1].board = nodeStack[depth].board;
            nodeStack[depth+1].board.updateBoard(
                    (nodeStack[depth].isMaxNode ? color : -color),
                    *nodeStack[depth].moveIterator);
            nodeStack[depth].prevIterator = nodeStack[depth].moveIterator;
            nodeStack[depth].moveIterator++;

            // If the next depth is not at the depth limit
            if (depth + 1 < depthLimit) {
                depth++;

                // Initialize next node in stack
                nodeStack[depth].isMaxNode = !nodeStack[depth-1].isMaxNode;
                nodeStack[depth].score =
                    (nodeStack[depth].isMaxNode ? INT_MIN : INT_MAX);
                nodeStack[depth].alpha = nodeStack[depth-1].alpha;
                nodeStack[depth].beta = nodeStack[depth-1].beta;
                nodeStack[depth].board.findLegalMoves(
                        (nodeStack[depth].isMaxNode ? color : -color),
                        &nodeStack[depth].board.moves);

                /*
                std::unordered_map<int, std::list<int>> foo1
                    = nodeStack[depth].board.moves.find(killerMoves[depth][0]);
                std::unordered_map<int, std::list<int>> foo2
                    = nodeStack[depth].board.moves.find(killerMoves[depth][1]);

                if (foo1 != nodeStack[depth].lastMove
                    && foo2 != nodeStack[depth].lastMove) {
                    std::iter_swap(nodeStack[depth].board.moves.begin(), foo1);
                    std::iter_swap(std::next(nodeStack[depth].board.moves.begin()), foo2);
                }
                else if (foo1 != nodeStack[depth].lastMove) {
                    std::iter_swap(nodeStack[depth].board.moves.begin(), foo1);
                }
                else if (foo2 != nodeStack[depth].lastMove) {
                    std::iter_swap(nodeStack[depth].board.moves.begin(), foo2);
                }
                */

                nodeStack[depth].moveIterator =
                    nodeStack[depth].board.moves.begin();
                nodeStack[depth].prevIterator =
                    nodeStack[depth].moveIterator;
                nodeStack[depth].lastMove = nodeStack[depth].board.moves.end();
            }
            else {
                // The node is a leaf: evaluate heuristic and update values
                leafScore = heuristic.evaluate(
                        nodeStack[depth+1].board, color);

                if (nodeStack[depth].isMaxNode) {
                    if (leafScore > nodeStack[depth].score) {
                        nodeStack[depth].score = leafScore;
                        if (depth == 0) {
                            bestMove = nodeStack[0].prevIterator;
                        }
                    }

                    if (nodeStack[depth].score > nodeStack[depth].alpha) {
                        nodeStack[depth].alpha = nodeStack[depth].score;
                    }
                }
                else {
                    if (leafScore < nodeStack[depth].score) {
                        nodeStack[depth].score = leafScore;
                    }

                    if (nodeStack[depth].score < nodeStack[depth].beta) {
                        nodeStack[depth].beta = nodeStack[depth].score;
                    }
                }
            }
        }

        // If we are almost out of time, failure
        if (stopTimer(startTime) > 0.998*timeLimit) {
            std::pair<int, std::list<int>> move;
            move.first = -1;
            return move;
        }
    }

    return *bestMove;
}
