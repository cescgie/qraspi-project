mcts: mcts-default.c board.c node.c
	gcc -g -Wall board.c node.c mcts-default.c -o mcts-default.out -lm
mcts-parallel: mcts-mpi.c board.c node.c mpitimer.o
	mpicc -g -Wall mpitimer.o board.c node.c mcts-mpi.c -o mcts-mpi.out -lm
testBoard: testBoard.c board.c
	gcc -g -Wall board.c testBoard.c -o testBoard.out
playback: playback/play-back.c board.c
	gcc -g -Wall board.c playback/play-back.c -o playback/play-back.out
mpitimer:
	mpicc -g -c -Wall mpitimer.c -o mpitimer.o