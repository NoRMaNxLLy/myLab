#!/bin/bash

# mimic the basename(1) command
# basename /usr/bin/ls           ==> ls
# basename /usr/bin/foo.bar .bar ==> foo
basename() {
    shopt -s extglob
    pathname="$1"
    suffix="$2"

    if [[ $# == 0 || $# -gt 2 ]]; then
        echo "Usage: basename <pathname> [suffix]" 1>&2
        return 1
    fi

    if [[ -z $pathname ]]; then
        printf '\n'
        return
    fi

    # if pathname is entirely slashes, output a slash
    if [[ $pathname =~ ^/+$ ]]; then
        printf '/\n'
        return
    fi

    pathname="${pathname%%*(/)}"
    pathname="${pathname##*/}"
    pathname="${pathname%"$suffix"}"

    printf '%s\n' "$pathname"
}

basename "$@"
