#!/bin/bash
time ./mcts-default.out > playback/mcts-default-1.txt
time ./mcts-default.out > playback/mcts-default-2.txt
time ./mcts-default.out > playback/mcts-default-3.txt
mpirun -n 4 ./mcts-mpi.out > playback/mcts-mpi-1.txt
mpirun -n 4 ./mcts-mpi.out > playback/mcts-mpi-2.txt
mpirun -n 4 ./mcts-mpi.out > playback/mcts-mpi-3.txt