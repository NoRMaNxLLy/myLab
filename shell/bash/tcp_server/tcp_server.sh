#!/bin/bash

enable accept
port=8080
declare -A conns

broadcast_msg() {
    local fd="$1" msg="$2"
    local client="${conns[$fd]}"
    for peer_fd in "${!conns[@]}"; do
        [[ $fd == "$peer_fd" ]] && continue
        echo "[$client ($fd)] $msg" >&"$peer_fd"
    done
}

handle_conn() {
    local fd="$1"
    local client="${conns[$fd]}"
    local msg

    while read -u "$fd" -r msg; do
        echo "[$client] $msg"
        broadcast_msg "$fd" "$msg"
    done

    echo "$client $fd disconnected"
}

close_conn() {
    local fd="$1"

    unset "conns[$fd]"
    exec {fd}<&-
    exec {fd}>&-
}

main() {
    local fd client

    echo "listening on port 8080"
    while :; do
        if ! accept -v fd -r client $port; then
            echo "error accepting from $client" 1>&2
            continue
        fi
        echo "connection from $client fd $fd"
        conns["$fd"]="$client"
        handle_conn "$fd" &
        close_conn "$fd"
    done
}

main "$@"
