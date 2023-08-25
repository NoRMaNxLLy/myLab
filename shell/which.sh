#!/bin/sh

which() {
    args="$@"

    OLDIFS="$IFS"
    IFS=:
    set -- $PATH
    IFS="$OLDIFS"

    for arg in $args; do
        for dir in "$@"; do
            if test -x "$dir/$arg"; then
                echo "$dir/$arg"
                continue 2
            fi
        done
        echo "no $arg in ($PATH)" 1>&2
    done
}

which "$@"
