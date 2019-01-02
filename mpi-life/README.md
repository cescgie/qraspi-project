MPI-life
========

Game of Life on MPI

## Compiling

$> mpic++ life.cpp -o life

## Running

(restriction: size of the input grid should be dividable by the number of processors)
example for give input (N=100)

&> mpirun -np 10 --hostfile hosts ./life input.txt

If program terminated with no errors, the output is written into output.txt file.

## Output

Output for a given input.txt is in Run1.txt file.
Output for 10 generations, printing to file every generation and the same grid as the first is in Run2.txt