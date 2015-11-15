#remove indexes, found in d-part2-v2
while(<>){
	next if /INDEX:/;
	print;
}
