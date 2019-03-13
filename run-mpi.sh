#!/bin/bash

infoPrompt() {
    case $1 in  
        ("run") 
            echo "========================="
            echo "  Welcome in Othello!!!  "
            echo " "
            echo "     ● ● ● ● ○ ○ ○ ○     "
            echo "     ● ● ● ● ○ ○ ○ ○     "
            echo "     ● ● ● ● ○ ○ ○ ○     "
            echo "     ● ● ● ● ○ ○ ○ ○     "
            echo "     ○ ○ ○ ○ ● ● ● ●     " 
            echo "     ○ ○ ○ ○ ● ● ● ●     " 
            echo "     ○ ○ ○ ○ ● ● ● ●     " 
            echo "     ○ ○ ○ ○ ● ● ● ●     "
            echo " "
            echo "========================="
        ;; 
        ("end") 
            echo "========================="
            echo "        Bye bye!         "
            echo "========================="
        ;;
        (*) 
            echo "========================="
            echo "        Bye bye!         "
            echo "========================="
        ;; 
    esac
}

askPrompt(){
    echo " "
    read -p "Start a new game? (y/n): " newGame </dev/tty
    case $newGame in  
        y|Y|j|J) checkHosts ;; 
        n|N) infoPrompt "end" ;;
        *) askPrompt ;; 
    esac
}

checkHosts(){
    # check if file hosts exists
    if [ ! -f ./hosts ]; then
        echo "File 'hosts' is not found! Please create one."
        infoPrompt "end"
    elif [ ! -s ./hosts ]; then # check if file hosts empty
        echo "File 'hosts' is empty. Please insert available hosts."
        infoPrompt "end"
    else 
        # if hosts file exists then remove it
        if [ -e ./files ]; then
            #remove hosts file
            rm ./files
        fi

        #write new hosts file
        while IFS='' read -r line || [[ -n "$line" ]]; do
            echo $line
            ping -c1 -W1 $line  && 
            echo " " && 
            echo "	CONNECTED TO $line" && 
            echo -e "$line" >> files || 
            echo "	CANNOT REACH $line" && 
            echo " "
        done < "hosts"

        sleep 1

        echo "AVAILABLE HOSTS: "
        cat files
        echo " "

        askNode
    fi
}

askNode(){
    read -p "How many number of processes should we use?: " nodesNumber </dev/tty
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
    read -p "Ready? (y/n): " ready </dev/tty
    case $ready in  
        y|Y|j|J) startProcesses ;; 
        n|N) askPromptReady;;
        *) askPrompt ;; 
    esac
}

startProcesses(){
    mpirun -f files -n $nodesNumber ./mcts-mpi.out
    askPrompt
}

#run
infoPrompt "run"
askPrompt
