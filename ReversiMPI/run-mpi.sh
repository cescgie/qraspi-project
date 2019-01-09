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
        y|Y|j|J) checkHosts $1 ;; 
        n|N) infoPrompt "end" ;;
        *) askPrompt ;; 
    esac
}

checkHosts(){
    #remove hosts file
    rm ./files

    #write new hosts file
    while IFS='' read -r line || [[ -n "$line" ]]; do
	ping -c1 -W1 $line  && 
	echo " " && 
	echo "	CONNECTED TO $line" && 
	echo -e "$line" >> files || 
	echo "	CANNOT REACH $line" && 
	echo " "
    done < "$1"

    sleep 1

    echo "AVAILABLE HOSTS: "
    cat files
    echo " "

    askNode
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
askPrompt $1
