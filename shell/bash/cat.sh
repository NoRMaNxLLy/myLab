#!/bin/bash

# mimic the cat(1) command

# it is not perfect; it does not read bytes, it reads the input as lines
# with '\n' as a separator, if the input contains no '\n', it will not
# work as expected

cat() {
    if [[ $# -eq 0 ]]; then
        while IFS=$'\n' read -r line; do
            printf '%s\n' "$line"
        done
        return
    fi

    for f; do
        if [[ $f == '-' ]]; then
            # if stdin is a terminal, multiple '-' gets multiple pieces
            # of input from the terminal. if stdin is a file, multiple
            # '-' will read once from the file and the rest are
            # /dev/null
            if [[ -t 0 ]]; then
                f='/dev/stdin'
            else
                if [[ -z $got_eof ]]; then
                    f='/dev/stdin'
                    got_eof=1
                else
                    f='/dev/null'
                fi
            fi
        fi

        while IFS=$'\n' read -r line; do
            printf '%s\n' "$line"
        done < "$f"
    done
}

cat "$@"
