#!/usr/bin/perl
print "Content-type: text/html\n\n";

for($i = 1; $i <= 7; $i++)
{
	print "<h$i> Header </h$i>";
}
