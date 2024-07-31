#!/bin/bash

# mimic the head(1) command

# $ head -n<count> [FILE]...
head() {
    getopts 'n:' f
    count="${OPTARG:-10}"
    shift $((OPTIND - 1))

    if ((count < 0)) || [[ $count = *[!0-9]* ]]; then
        echo "invalid number: $count"
        return 1
    fi

    # output without header if zero or one argument is passed
    if (($# <= 1)); then
        mapfile -t -n "$count" lines < "${1:-/dev/stdin}"
        printf '%s\n' "${lines[@]}"
        return
    fi

    for f; do
        mapfile -t -n "$count" lines < "$f"
        printf '==> %s <==\n' "$f"
        printf '%s\n' "${lines[@]}"
        printf '\n'
    done
}

head "$@"
