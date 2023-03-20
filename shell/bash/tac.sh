#!/bin/bash

# mimic the tac(1) command

tac() {
    if ! [[ -t 0 ]]; then
        mapfile lines
    else
        mapfile lines < "$1"
    fi

    for ((i = ${#lines[@]}; i >= 0; i--)); do
        printf '%s' "${lines[$i]}"
    done
}

tac "$f"
