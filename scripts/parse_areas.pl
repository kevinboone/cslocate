#!/usr/bin/perl

use strict;

open IN, "<tmp/area.tbl" or die "Can't read area.tbl";
open OUT, ">src/area.c" or die "Can't write area.c";

print OUT "#include \"area.h\"\n";
print OUT "Area areas[] = {\n"; 
  
while (my $line = <IN>) 
  {
  chomp ($line);

  my @fields = split ('\|', $line);
  my $desc = $fields[1];
  $desc =~ s/\"/\\\"/g;

  my @subfields = split (' ', $fields[0]);
  foreach my $subfield (@subfields)
    {
    $subfield =~ s/%/[A-Z]/g;
    print OUT "{\"\^$subfield\", \"$desc\"},\n";
    }
  }

close IN;

open IN, "<tmp/country.tbl" or die "Can't read country.tbl";

while (my $line = <IN>) 
  {
  chomp ($line);

  my @fields = split ('\|', $line);
  my $desc = $fields[1];
  $desc =~ s/\"/\\\"/g;

  my @subfields = split (' ', $fields[0]);
  foreach my $subfield (@subfields)
    {
    $subfield =~ s/%/[A-Z]/g;
    print OUT "{\"\^$subfield\", \"$desc\"},\n";
    }
  }

print OUT "{0, 0}\n};\n";
close OUT;
close IN;


