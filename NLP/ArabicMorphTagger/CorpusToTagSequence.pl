#!/usr/bin/perl -w


use lib ".";

use MorphTranslation;

$sent = "";
while(<STDIN>) {
  unless (/^\s*\{sentence( #\d+)?\}\s*$/) {
    $parse = "";
    while (s/(\([^\)\(]+\))//) {
      $parse .= $1;   
    }
#    print STDERR "[$parse]\n";
    $parse = ParseToTagSequence($parse);
    $parse =~ s/[\[\]]//g ;

    $parse = join(" ",split(" ",$parse));

    $sent .= $parse . " ";
  }  
  else { 
    print "$sent\n" if ($sent);
    $sent = "";
  }
}
print "$sent\n" if ($sent);



