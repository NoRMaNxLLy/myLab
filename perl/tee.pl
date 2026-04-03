#!/usr/bin/perl
use strict;
use warnings;

my @handles;
for my $f (@ARGV) {
	my $fh;
	open $fh, ">", $f or die "cant open file $f: $!";
	push @handles, $fh;
}

while (<STDIN>) {
	print STDOUT $_;
	for my $fh (@handles) {
		print $fh $_ or die "cant write to file $fh: $!";
	}
}
