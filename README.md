# Othello MPI
Paralleles Othello-Programm mit MPI

## Environment
* Ubuntu 16.04+
* MPI
* Qt5
* Doxygen

## Config
- Create new file and named it "hosts", write all available hosts on each line separately

## Compile
```
$ make mpitimer
$ make mcts-parallel
```

## Running
```
$ ./run-mpi.sh
```

## Testing
```
$ make testBoard
$ mpirun n <nodesNumber> ./testBoard.out
```

## Doxigen-Documentation
```
$ doxygen Doxyfile
```
