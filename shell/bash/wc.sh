#!/bin/bash

# mimic the wc(1) command
# i did not know how to count bytes with pure bash, only character count
# option (-m)
wc() {
    while getopts 'mlwc' f; do
        case "$f" in
            m) dochars=1;;
            l) dolines=1;;
            w) dowords=1;;
            c) echo '-c is not implemented' 1>&2;;
            \?) exit 1;;
        esac
    done
    shift $((OPTIND - 1))

    if [[ $# -eq 0 ]]; then
        files=( "/dev/stdin" )
    else
        files=( "$@" )
    fi

    total_lines=0
    total_words=0
    total_chars=0

    for f in "${files[@]}"; do
        [[ "$f" = "-" ]] && f='/dev/stdin'
        [[ -e "$f" ]] || { echo "$f: no such file or directory" 1>&2; continue ;}
        [[ -d "$f" ]] && { echo "$f: Is a directory" 1>&2; continue ;}

        mapfile lines < "$f"
        line_count="${#lines[@]}"
        word_count=0
        char_count=0

        for line in "${lines[@]}"; do
            for word in $line; do
                ((word_count++))
            done

            ((char_count += ${#line}))
        done

        # if have options, output what was specified.
        if [[ ${!do*} ]]; then
            [[ -n $dolines ]] && printf '%7d' "$line_count"
            [[ -n $dowords ]] && printf '%7d' "$word_count"
            [[ -n $dochars ]] && printf '%7d' "$char_count"
            printf ' %s\n' "$f"
        else
            printf '%7d%7d%7d %s\n' $line_count $word_count $char_count "$f"
        fi

        ((total_lines += line_count))
        ((total_words += word_count))
        ((total_chars += char_count))
    done

    # outoput total if having multiple files
    if [[ ${#files[@]} -gt 1 ]]; then
        if [[ ${!do*} ]]; then
            [[ -n $dolines ]] && printf '%7d' "$total_lines"
            [[ -n $dowords ]] && printf '%7d' "$total_words"
            [[ -n $dochars ]] && printf '%7d' "$total_chars"
            printf ' %s\n' "total"
        else
            printf '%7d%7d%7d %s\n' $total_lines $total_words $total_chars "total"
        fi
    fi
}

wc "$@"
