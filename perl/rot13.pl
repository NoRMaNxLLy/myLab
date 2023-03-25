#!/usr/bin/perl

use strict;
use warnings;

while (<>) {
    tr/a-zA-Z/n-za-mN-ZA-M/;
    print;
}
