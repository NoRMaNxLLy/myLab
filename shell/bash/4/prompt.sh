_git_branch() {
	local d=.
	local b=
	for _ in {1..7}; do
		if [[ -d $d/.git ]]; then
			IFS= read -r l <"$d/.git/HEAD"
			b="${l##*/}"
			break
		fi
		d="../$d"
	done

	PS1="\[\033[1;3m\]\w\[\033[0m\]\[\033[$((COLUMNS - ${#b}))G\033[1m\]$b
\[\033[1m\]\$\[\033[0m\] "
}

PROMPT_COMMAND=_git_branch
