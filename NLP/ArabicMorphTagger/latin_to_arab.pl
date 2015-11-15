

while(<>){
	s/\[//g; 
	s/\]\s*$//;
	@wordtags=split(/\]/); 
	foreach $wt (@wordtags){
		@morphs = ($wt=~/\(\S+ (\S+)\)/g);
		@tags = ($wt=~/\((\S+) \S+\)/g);
		map(tr/PJRG,;?'|>&<}AbptvjHxd*rzs\$SDTZEg_fqklmnhwYyFNKaui~o{/\x81\x8D\x8E\x90\xA1\xBA\xBF\xC1\xC2\xC3\xC4\xC5\xC6\xC7\xC8\xC9\xCA\xCB\xCC\xCD\xCE\xCF\xD0\xD1\xD2\xD3\xD4\xD5\xD6\xD8\xD9\xDA\xDB\xDC\xDD\xDE\xDF\xE1\xE3\xE4\xE5\xE6\xEC\xED\xF0\xF1\xF2\xF3\xF5\xF6\xF8\xFA\xC5/,@morphs);
		print "[";
		
		foreach $m (@morphs){
			print "(" . shift(@tags) . " $m)"
		}
		
		print "]";
		
	}
	
	print "\n";
	
}



