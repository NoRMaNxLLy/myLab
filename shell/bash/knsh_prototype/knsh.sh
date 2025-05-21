#!/usr/bin/bash

# a prototype for kunnash

# shellcheck disable=SC2128
# shellcheck disable=SC2164
shopt -s extglob

#KNSH_DIR="${KNSH_DIR:-$HOME/.local/cache}"
KNSH_DIR="test"
EDITOR="${EDITOR:-vi}"

# fatal() prints the fatal message $1 and exit with status $2
fatal() {
    printf '\033[31m%s\033[0m\n' "$1" 1>&2
    exit "$2"
}

# error() prints an error message
error() {
    printf '\033[31m%s\033[0m\n' "$1" 1>&2
}

# wrqh_exist checks if the given waraqah exist or not
wrqh_exist() {
    local wrqh="$1"
    if ! [[ -d $wrqh ]]; then
        return 1
    fi
    return 0
}

# knsh_next_id() returns the next usable waraqah ID
knsh_next_id() {
    local id
    read -r id < .id_counter
    printf "%d" $((++id))
}

# knsh_exist() return 0 if the kunnash exists, otherwise it returns 1
knsh_exist() {
    local knsh="$1"
    if ! [[ -d $knsh && -f $knsh/knsh.dex ]]; then
        return 1
    fi
    return 0
}

# knsh_new() creates a new kunnash
knsh_new() {
    local knsh="$1"

    if ! mkdir "$knsh" 2>/dev/null; then
        return 1
    fi

    touch "$knsh/knsh.dex"
    touch "$knsh/.id_counter"

    printf "%d\n" 0 > "$knsh/.id_counter"
}

# go to the given kunnash
knsh_cd() {
    cd "$1" >/dev/null 2>&1
}

# knsh_tmp_wrqh() addes a tmp wrqh to .tmp. the waraqah can be added to
# the kunnash with knsh_new_wrqh()
knsh_tmp_wrqh() {
    local wrqh_id="$1"
    [[ -d .tmp ]] || mkdir .tmp
    mkdir ".tmp/$wrqh_id" 2>/dev/null
    touch ".tmp/$wrqh_id/README.md"
}

# knsh_new_wrqh() adds a new waraqah to the kunnash
knsh_new_wrqh() {
    local wrqh="$1"
    local wrqh_id

    wrqh_id=$(knsh_next_id)

    mv "$wrqh" "$wrqh_id"
}

# knsh_addto_dex() add a new  waraqah or kunnash to the index of the
# kunnash. $1 is the name of the kunnash, $2 is the Item ID
knsh_addto_dex() {
    local id="$1";
    local title="$2";

    printf '%s\t%s\t%(%Y%m%dT%H%M%S)T\t%(%Y%m%dT%H%M%S)T\n' \
        "$id" \
        "$title" \
        -1 -1 >> "knsh.dex"
}

# knsh_edit_wrqh() edits a waraqah in the given kunnash
knsh_edit_wrqh() {
    local wrqh_id="${1##*/}" knsh="${2%/*}"
    "$EDITOR" "$knsh/$wrqh_id/README.md"
}

# knsh_titles() prints waraqahs titles
knsh_titles() {
    local knsh="$1"
    local inner_knsh=() id title

    while IFS= read -r line; do
        IFS=$'\t' read -r id title _ <<< "$line"
        if [[ $id == k ]]; then
            inner_knsh+=("$title")
        fi
        printf '%s\t%s\n' "${knsh:+$knsh/}$id" "$title"
    done < "${knsh:+$knsh/}knsh.dex"

    for k in "${inner_knsh[@]}"; do
        knsh_titles "${knsh:+$knsh/}$k"
    done
}

# knsh_search() searches for the RE in the given kunnash. returns the
# waraqahs that matched the RE
knsh_search() {
    local re="$1" knsh="$2"
    local id wt
    mapfile -t matches < <( \
        find "$knsh" -type f \
        ! -name "knsh.dex" ! -name ".id_counter" \
        -exec grep -r -i -l "$re" {} \+ \
    )

    for id in "${matches[@]%/*}"; do
        IFS= read -r wt < "$id/README.md"
        printf "%s\t%s\n" "$id" "$wt"
    done
}

# knsh_del_wrqh() deletes a wrqh
knsh_del_wrqh() {
    :
}

cmd_new_knsh() {
    local knsh="${1%/}"

    if knsh_exist "$knsh"; then
        fatal "$FUNCNAME: $knsh already exist" 1
    fi

    if [[ $knsh =~ ^.*/.*$ ]]; then
        local pknsh="${knsh%/*}"
        knsh="${knsh##*/}"
        knsh_cd "$pknsh"
    fi

    if ! knsh_new "$knsh"; then
        fatal "$FUNCNAME: could not create a kunnash $knsh" 1
    fi

    knsh_addto_dex k "$knsh"
}

# CLI command to add a new waraqah.
cmd_new() {
    local knsh="$1"
    local wrqh_id wrqh_title

    if [[ -n $knsh ]]; then
        knsh_cd "$knsh"
    fi

    knsh_tmp_wrqh $$
    "$EDITOR" .tmp/$$/README.md

    wrqh_id=$(knsh_next_id)
    knsh_new_wrqh ".tmp/$$" "$wrqh_id"
    IFS= read -r wrqh_title < "$wrqh_id/README.md"

    knsh_addto_dex "$wrqh_id" "$wrqh_title"
    echo "$wrqh_id" > ".id_counter"
}

# CLI command to print the titles of one or more kunnash
cmd_titles() {
    local knsh="$1"

    if [[ -z $knsh ]]; then
        knsh_titles .
        return
    fi

    for knsh; do
        if ! knsh_exist "$knsh"; then
            fatal "$FUNCNAME: $knsh does not exist" 1
        fi
        knsh_titles "$knsh"
    done
}

cmd_search() {
    local re="$1" knsh="$2"
    shift 1

    if [[ -z $re ]]; then
        return
    fi
    if [[ -z $knsh ]]; then
        knsh_search "$re" .
        return
    fi

    for knsh; do
        if ! knsh_exist "$knsh"; then
            error "$knsh does not exist"
        fi
        knsh_search "$re" "$knsh"
    done
}

# CLI command to select and open a waraqah.
# args:
# * re,REGEX is a regular expression. it least one re should be given
# * k,KNSH is the kunnash to search in. zero or more kunnashes can be
#   given
cmd_select() {
    declare -a knsh re matches
    local choice

    while (( $# >= 1 )); do
        arg="$1"
        case "$arg" in
            k,*)  knsh+=("${arg#k,}");;
            re,*) re+=("${arg#re,}");;
        esac
        shift 1
    done

    [[ -z $re ]] && return 1
    [[ -z $knsh ]] && knsh=(.)

    for k in "${knsh[@]}"; do
        if ! knsh_exist "$k"; then
            error "kunnash does not exist: $k"
            continue
        fi
        for r in "${re[@]}"; do
            while IFS= read -r line; do
                matches+=("$line")
            done < <(knsh_search "$r" "$k")
        done
    done

    select choice in "${matches[@]}"; do
        echo "${choice%$'\t'*}/README.md"
        break
    done
}

# CLI command to import an external waraqah to the kunnash
# TODO: why not accept a list of waraqahs instead of one?
cmd_import() {
    local  import_wrqh="${1%/}" knsh="$2"
    local wrqh_id wrqh_title

    [[ -z "$knsh" ]] && knsh=.
    if ! knsh_exist "$knsh"; then
        fatal "kunnash does not exist: $knsh" 1
    fi

    if ! wrqh_exist "$import_wrqh"; then
        fatal "waraqah does nost exist: $import_wrqh" 1
    fi

    if ! [[ -f $import_wrqh/README.md ]]; then
        fatal "waraqah does not have a README.md: $import_wrqh" 1
    fi

    ## if everthing is fine add the waraqah and update the index
    wrqh_id=$(knsh_next_id)
    knsh_new_wrqh "$import_wrqh" "$wrqh_id"

    IFS= read -r wrqh_title < "$wrqh_id/README.md"
    knsh_addto_dex "$wrqh_id" "$wrqh_title"
}

main() {
    local root_knsh="$KNSH_DIR" knsh cmd

    if ! knsh_exist "$root_knsh"; then
        knsh_new "$root_knsh"
    fi
    knsh_cd "$root_knsh"

    cmd="$1"
    shift
    case "$cmd" in
        new_knsh) cmd_new_knsh "$1" "$@";;
        new)      cmd_new "$@"          ;;
        titles)   cmd_titles "$@"       ;;
        search)   cmd_search "$@"       ;;
        select)   cmd_select "$@"       ;;
        import)   cmd_import "$@"       ;;
        "")       :                     ;;
            *) fatal "$cmd is not a command" 1
        esac
}

if [[ $0 != *test.sh ]]; then
    main "$@"
fi
