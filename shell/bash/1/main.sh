#!/bin/bash

declared_funcs() {
    mapfile -t funcs < <(declare -F)
    echo "${funcs[@]##* }"
}

declared_funcs
