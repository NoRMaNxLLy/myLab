#!/bin/bash

# default duration: 25m
duration="1500"
prefix=
stop_prefix=

parse_duration() {
    dur="$1"
    h=0 m=0 s=0

    if ! [[ $dur =~ h|m|s ]]; then
        printf 'missing unit in duration "%d"\n' "$dur" 1>&2
        exit 1
    fi

    # calclulate in positive. the negative sign will be added back at
    # the end of the function
    [[ ${1:0:1} == '-' ]] && dur="${dur#-}"

    if [[ $dur =~ [0-9]*h ]]; then
        h="${dur%%h*}"
        dur="${dur##*h}"
    fi

    if [[ $dur =~ [0-9]*m ]]; then
        m="${dur%%m*}"
        dur="${dur##*m}"
    fi

    if [[ $dur =~ [0-9]*s ]]; then
        s="${dur%%s*}"
        dur="${dur##*s}"
    fi

    ((duration = h * 3600 + m * 60 + s))

    [[ ${1:0:1} == '-' ]] && ((duration *= -1))
}

output() {
    sign=''
    if ((remains < 0)); then
        local sign='-'
        ((remains *= -1))
    fi

    ((hours = remains / 3600))
    ((remains %= 3600))
    ((minutes = remains / 60))
    ((remains %= 60))

    printf '%s %s' $prefix $sign
    ((hours != 0)) && printf '%02d:' $hours
    printf '%02d:%02d\n' $minutes $remains
}

main() {
    case "$1" in
        start)
            [[ -n $2 ]] && parse_duration "$2"
            # -1 represents the current time. read bash(1).
            printf '%(%s)T %d\n' -1 $duration > "/tmp/pomo"
            ;;
        stop)
            rm "/tmp/pomo" 2>/dev/null
            exit 0
    esac

    if ! [[ -e /tmp/pomo ]]; then
        printf '%s\n' $stop_prefix
        return 0;
    fi

    read start duration < "/tmp/pomo"
    ((end = start + duration))
    printf -v now "%(%s)T"
    ((remains = end - now))
    output
}

main "$@"
