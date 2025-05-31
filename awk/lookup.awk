# lookup value v of item k

BEGIN {
	RS=""
	FS="\n"
}

{
	for (i = 1; i <= NF; i++) {
		split($i, fields, "\t")
		if (fields[1] != k) continue
		if (fields[2] == v) print $0
	}
}
