#!/usr/bin/bash

TESTING=y
KNSH_DIR=test

source knsh.sh
cd "$KNSH_DIR"

test_knsh_tmp_wrqh() {
    knsh_tmp_wrqh $$
    if ! [[ -f .tmp/$$/README.md ]]; then
        echo "FAILED $FUNCNAME" 1>&2
        return 1
    fi

    echo "PASSED $FUNCNAME"
    rm -r ".tmp/$$"
}
test_knsh_tmp_wrqh

test_knsh_new() {
    [[ -d _test_ ]] && rm -r "_test_"
    knsh_new "_test_"
    if ! [[ -d _test_ || -f _test_/knsh.dex ]]; then
        echo "FAILED $FUNCNAME" 1>&2
        return 1
    fi
    knsh_new "_test_/__test__"
    if ! [[ -d _test_ || -f _test_/knsh.dex ]]; then
        echo "FAILED $FUNCNAME" 1>&2
        return 1
    fi
    echo "PASSED $FUNCNAME"

    rm -r "_test_"
}
test_knsh_new
