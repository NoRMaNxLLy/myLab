# unback a bundle into separate files
{
	f = $1
	r = f FS
	sub(r, "")
	print($0, ">", f)
}
