#!/bin/bash

# mimic the tac(1) command

tac() {
    # if stdin is not terminal
    if ! [[ -t 0 ]]; then
        mapfile -t lines
        for ((i = ${#lines[@]} - 1; i >= 0; i--)); do
            printf '%s\n' "${lines[$i]}"
        done
        return
    fi

    for f; do
        mapfile -t lines < "$f"
        for ((i = ${#lines[@]} - 1; i >= 0; i--)); do
            printf '%s\n' "${lines[$i]}"
        done
    done
}

tac "$@"
