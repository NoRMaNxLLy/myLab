NF > 0 {
	f = 1
	e = expr()
	if (f <= NF) printf("error at %s\n", $f)
	else printf("\t%.8g\n", e)
}

function expr(  e) {
	e = term() #term | term [+-] term

	while ($f == "+" || $f == "-")
		e = $(f++) == "+"? e + term(): e - term()
	return e
}

function term(  e) {
	e = factor() # factor | factor [*/] factor
	while ($f == "*" || $f == "/")
		e = $(f++) == "*"? e * factor(): e / factor()
	return e
}

function factor(  e) { # number | (expr)
	if ($f ~ /^[+-]?([0-9]+[.]?[0-9]*|[.][0-9]+)$/) {
		return $(f++)
	} else if ($f == "(") {
		f++
		e = expr()
		if ($(f++) != ")")
			printf("error: missing ) at %s\n", $f)
		return e
	} else {
		printf("error: expected number or ( at %s\n", Sf)
	   return 0
	}
}
