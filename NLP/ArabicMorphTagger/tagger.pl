#!/usr/bin/perl
print "Content-type: text/html\n\n";
#print "lllaaalllll";

use lib ".";

use AraMorph;
use BuckToRoy;

$to_tag ="·„«–«";

my $file = "temp";
my $redirect = "";


#Run BAMA (in yeda, I needed to run 'setenv LANG C' before this worked, maybe you don't need it):
$out = AraMorph($to_tag);

#print $out;

#Convert BAMA's output to Roy format
$out = BuckToRoy($out);

#Tag:
#$out = `./MTTest.pl -dir test1 $file.roy arabic.lm arabic.lex.prob`;

#$out = `perl latin_to_arab.pl < test1/tagging-$file.roy`;
#print "hhh\n";
print $out;

#open(OUT,"<test1/tagging-$file.roy");

#while(<OUT>){
#	print;
#}

#close(OUT);

