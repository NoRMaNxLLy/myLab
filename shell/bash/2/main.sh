#!/usr/bin/bash

func1() {
    local var="$FUNCNAME"
    echo "$FUNCNAME var=$var"
    func2
    echo "$FUNCNAME var=$var"
}

func2() {
    echo "$FUNCNAME var=$var"
    var="returned from $FUNCNAME"
}

func1
