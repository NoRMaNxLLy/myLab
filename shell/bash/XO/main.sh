#!/bin/bash

# print the grid -_-
print_grid() {
    printf '\tA\tB\tC\n'
    for row in {1..3}; do
        printf '%d\t' $row
        for i in {1..3}; do
            printf '%s\t' $1
            shift
        done
        printf '\n'
    done
}

# check if we have a winner
check_winner() {

    # first row
    if [[ $1 != '.' && $1 == $2 && $2 == $3 ]]; then
        echo "$1"
    fi
}

main() {
    grid=( [1]=. [2]=.  [3]=.  [4]=.  [5]=.  [6]=.  [7]=.
        [8]=. [9]=. )

    for t in {1..9}; do
        # if won print the table and break the loop. mark the winner
        # if the action is invalid
    done

    # if someone is won print it -_-
    # otherwise draw
}

main
