# generate and endless stream of cliches
# input: lines in the form subject:predicate
# output: lines of random subject & predict

BEGIN { FS = ":"; srand() }
{ s[NR] = $1; p[NR] = $2 }
END { for (;;) print s[randint(NR)], p[randint(NR)] }

# return a random int from 1 to n
function randint(n) { return int(n * rand()) + 1 }
