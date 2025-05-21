#!/bin/sh

func1() {
    echo "inside func1"
}

if test "$TESTING" = 'y'; then
    echo "test mode"
    return
fi

func1
