#!/bin/bash

infoPrompt() {
    case $1 in  
        ("run") 
            echo "========================"
            echo "Welcome in Othello!!!"
            echo "========================"
        ;; 
        ("end") 
            echo "Bye bye!"
        ;;
        (*) echo "Bye bye!" 
        ;; 
    esac
}

askPrompt(){
    echo " "
    read -p "Start a new game? (y/n) " newGame </dev/tty
    case $newGame in  
        y|Y|j|J) askNode ;; 
        n|N) infoPrompt "end" ;;
        *) askPrompt ;; 
    esac
}

askNode(){
    read -p "How many number of processes should we use? " nodesNumber </dev/tty
    checkGivenNodesNumber
}

checkGivenNodesNumber(){
    if [[ -z "$nodesNumber" ]]; then
        printf '%s\n' "No input :("
        askNode
    elif ! [[ "$nodesNumber" =~ ^[0-9]+$ ]]; then
        printf '%s\n' "No input :("
        askNode
    elif [[ "$nodesNumber" -gt 12 ]]; then
        printf '%s\n' "We do not have that many number of processes :("
        askNode
    else
        askPromptReady
    fi
}

askPromptReady(){
    read -p "Ready? (y/n) " ready </dev/tty
    case $ready in  
        y|Y|j|J) startProcesses ;; 
        n|N) askPromptReady;;
        *) askPrompt ;; 
    esac
}

startProcesses(){
    mpirun -f hostsfile -n $nodesNumber ./mcts-mpi.out
    askPrompt
}

#run
infoPrompt "run"
askPrompt
