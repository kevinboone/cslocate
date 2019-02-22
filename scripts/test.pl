#!/usr/bin/perl -w
use strict;

open IN, "<scripts/test.dat" or die "Can't open scripts/test.dat";

while (my $line = <IN>)
  {
  chomp ($line);
  system ("./cslocate $line");
  }

