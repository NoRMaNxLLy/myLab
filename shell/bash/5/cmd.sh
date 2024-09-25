#!/bin/bash

progname="$0"
cmds=(add del edit clean change)

# $1: progname
# $2: current word being completed
# $3: previous word
comp_start() {
	local cw="$2" pw="$3"

	if [[ $pw == "$progname" && $cw == -* ]]; then
		comp_doopts "$cw"
		return
	fi
	if [[ $pw == "$progname" || $pw == -* ]]; then
		comp_dosubcmds "$cw"
		return
	fi
}

# complete subcommands
comp_dosubcmds() {
	local cmd="$1"
	for c in "${cmds[@]}"; do
		[[ $c == $cmd* ]] && echo "$c"
	done
}

# complete command or subcommand options
comp_doopts() {
	local opt="${1#-}" opts=(l d a)

	[[ -z $opt ]] && printf '%s\n' "${opts[@]}" && return
	for o in "${opts[@]}"; do
		[[ $o == "$opt" ]] && echo "-$o"
	done
}

if [[ -n $COMP_LINE ]]; then
	comp_start "$@"
	exit
fi
