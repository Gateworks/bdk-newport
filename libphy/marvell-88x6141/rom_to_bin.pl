#!/usr/bin/perl

# This script converts a rom file (read from STDIN)
# to a raw binary file (written to STDOUT).

use strict;
use warnings;

my ($hexstring, $bin, $lsb, $msb);

while (<STDIN>) {
    s{\x0D}{}g;
    chomp;

    if (m/[0-9a-fA-F]{3}$/) {
        # Each line in the rom file is a 16-bit integer represented as a
        # 3-hexdigit number.

        $lsb = substr $_, 1, 2;
        $msb = "0" . substr $_, 0, 1;

        $hexstring .= $lsb . $msb;
    } else {
        print STDERR "invalid rom file\n";
        exit 1;
    }
}

$bin = hexstring_to_raw_binary($hexstring);

print STDOUT $bin;

exit 0;

###########################

sub hexstring_to_raw_binary {
    my $rawbin = $_[0];

    $rawbin =~ s/([0-9a-fA-F]{2})/ sprintf("%c",hex($1)) /ges;

    return $rawbin;
}
