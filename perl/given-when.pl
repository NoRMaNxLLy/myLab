#!/usr/bin/perl
# The "switch" feature is discouraged for new code and is retained for
# backward compatibility. see perlsyn.

use v5.14;
use strict;
use warnings;

my $grade = <STDIN>;

given ($grade) {
	when(<= 100) {print "A\n"};
}
