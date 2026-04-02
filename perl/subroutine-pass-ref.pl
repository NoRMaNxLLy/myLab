@c = (1, 2, 3, 4);
@d = (8, 9, 10);
($aref, $bref) = func(\@c, \@d);
print "@$aref has more than @$bref\n";

sub func {
    my ($cref, $dref) = @_;

	return ($cref, $dref) if (@$cref > @$dref);
	return ($dref, $cref);
}
