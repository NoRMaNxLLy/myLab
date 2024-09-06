#!/bin/bash

mygrep() {
    local re="$1"; shift

    if ! [[ -t 0 ]]; then
        while IFS= read -r line; do
            [[ $line =~ $re ]] && echo "$line"
        done
        return
    fi

    for f in "$@"; do
        while IFS= read -r line; do
            [[ $line =~ $re ]] && echo "$f:$line"
        done < "$f"
    done
}

mygrep "$@"
