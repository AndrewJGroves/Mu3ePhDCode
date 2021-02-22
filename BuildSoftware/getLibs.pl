#!/usr/bin/perl

use strict;
my @linkTxtFiles;
my %libs;

if ($#ARGV != 0 ) {
  die ("Give a dir as arg");
}

open(LINKTXT,"find $ARGV[0] -type f -name link.txt|") or die("Could not find libs");
while(<LINKTXT>) {
  my $linkTxt = $_;
  chomp($linkTxt);
  push(@linkTxtFiles,$linkTxt);
}

foreach my $ltf (@linkTxtFiles) {

  $/ = undef;
  open my $ltf, '<', $ltf or die;
  my $data = <$ltf>;
  close $ltf;

  my @parts = split(":",$data);
  foreach my $part (@parts) {
    $part =~ s/.*,//;
    if ($part =~ /.*\/lib$/) {
      $libs{$part} = 1;
    }
    if ($part =~ /.*\/lib64$/) {
      $libs{$part} = 1;
    }
  }
}

foreach my $l (keys(%libs)) {
  print("$l\n");
}


