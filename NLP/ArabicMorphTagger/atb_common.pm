package atb_common;

use strict;
use Class::Struct;

struct (WordAnal => {
	word => '$',
	analyses => '@'
});

require Exporter;

our @ISA = qw(Exporter);
our @EXPORT = qw(
  REMOVEMARKSWORD
  REMOVEMARKSPUNC
  REMOVE_VOWELS
  IS_EQUAL_ARAB
  PERFORM_AUTO_SEP
  DEF_FORMAT
  WordAnal
  READ_ANALYSES
  READ_CORPUS
  READ_MAP
  HEX_TO_CHAR
  MATCH_TAG
  MATCH_ANALYSIS
  @SIGTAGS
  @SIGTAGSCOLL
  @FUNCTAGS
  @FUNCTAGSCOLL
  %COLLAPSEHASH
  GET_VOWELS_PATTERN
  FIND_CORR_SEG
);



sub FIND_CORR_SEG{
	my $ganal = shift;
	my @oanallist = @_;
	my @cseg = ();
	foreach my $oanal (@oanallist){
		if (IS_SAME_SEG($ganal,$oanal)){
			push @cseg, $oanal;
		}
	}
	return @cseg;
}


sub IS_SAME_SEG{
	my ($ganal,$oanal) = @_;
	$ganal .= " "; $oanal .= " ";
	my @gmorphs = ($ganal =~ /\(\S+ (\S+)\)\s/g);
	my @omorphs = ($oanal =~ /\(\S+ (\S+)\)\s/g);
	
	my $gword = join(" ", @gmorphs);
	my $oword = join(" ", @omorphs);
	
	my @oword = split(//, $oword);
	my @gword = split(//,$gword);
	
	for(my $i=0; $i<@gword;$i++){
		if ( ($oword[$i] eq ' ' or $gword[$i] eq ' ')
				and ($oword[$i] ne ' ' or $gword[$i] ne ' ') ) { return 0; }
	}
	
	return 1;
}

#####################################
sub MATCH_ANALYSIS{
	my $analysis = shift;
	
	#in buckv1 it's NOUN, in atb2/3/1v3 it's NUM
	if ($analysis !~ /\d/ and $analysis !~ /NUMERIC_COMMA/){
		$analysis =~ s/([^\+\/]+)\/NUM/$1\/NOUN/;
	}
	
	#error in atb3
	#bAlAjmAE		[<ijomAE_1]	bi/PREP+Al/DET+<ijomAE/NOUN+i/CASE_DEF_GEN+i/CASE_DEF_GEN
	$analysis =~ s/i\/CASE_DEF_GEN\+i\/CASE_DEF_GEN$/i\/CASE_DEF_GEN/;
	
	$analysis =~ s/^\s*F\/NOUN\s*$/_\/PUNC/;
	
	$analysis =~ s/lawolA\/CONJ/lawo\/SUB_CONJ\+lA\/NEG_PART/;
	
  #SOLUTION 1: (muno*u) [muno*u_1] muno*u/CONJ
  #   (GLOSS):  + since/ago + 
  #SOLUTION 2: (muno*u) [muno*u_1] muno*u/PREP

	#* SOLUTION 1: (muno*u) [muno*u_1] muno*u/PREP
  #   (GLOSS): since/ago
  #SOLUTION 2: (muno*u) [muno*u_1] muno*u/SUB_CONJ
  #   (GLOSS): since/starting from

	#this was actually solved by adding prep to the dictStems of buckwalter, updated atb2-buckv1.0 manually

#	SOLUTION 4: (<in~a) [<in~a_1] <in~a/FUNC_WORD
#     (GLOSS):  + that/indeed + 

#  SOLUTION 4: (<in~a) [<in~a_1] <in~a/SUB_CONJ
#     (GLOSS): that
#* SOLUTION 5: (<in~a) [<in~a_2] <in~a/PART
#     (GLOSS): indeed

	$analysis =~ s/<in~a\/PART/<in~a\/SUB_CONJ/;

#  SOLUTION 2: (siwaY) [siwaY_1] siwaY/PREP
#     (GLOSS):  + other than/except for + 

#* SOLUTION 2: (siwaY) [siwaY_1] siwaY/NEG_PART
#     (GLOSS): other than/except for

	$analysis =~ s/siwaY\/PREP/siwaY\/NEG_PART/;
	
	
	#* SOLUTION 1: (walaw) [law_1] walaw/SUB_CONJ
  #   (GLOSS): even if
  #SOLUTION 2: (walaw) [law_1] wa/CONJ+law/SUB_CONJ
  #   (GLOSS): and + if
  $analysis =~ s/wa\/CONJ\+law\/SUB_CONJ/walaw\/SUB_CONJ/;
  
  
  #  SOLUTION 1: (bayoda) [bayoda_1] bayoda/CONJ
  #   (GLOSS):  + whereas/however + 
     
  #   * SOLUTION 1: (bayoda) [bayoda_1] bayoda/ADV
  #   (GLOSS): whereas/however
	$analysis =~ s/bayoda\/CONJ/bayoda\/ADV/;
	
	#  SOLUTION 1: (kayofa) [kayofa_1] kayofa/REL_PRON
  #   (GLOSS):  + how + 
  #SOLUTION 2: (kayofa) [kayofa_1] kayofa/INTERROG_PART
  #   (GLOSS):  + how + 

#* SOLUTION 1: (kayofa) [kayofa_1] kayofa/REL_ADV
 #    (GLOSS): how
  #SOLUTION 2: (kayofa) [kayofa_2] kayofa/INTERROG_PART
   #  (GLOSS): how
  
  $analysis =~ s/kayofa\/REL_PRON/kayofa\/REL_ADV/;
  
  
	#SOLUTION 1: (kilA) [kilA_1] kilA/FUNC_WORD
  #   (GLOSS):  + both of + 
  #SOLUTION 2: (kal~A) [kal~A_1] kal~A/INTERJ
  #   (GLOSS):  + not at all/definitely not + 
       
  #     SOLUTION 1: (kilA) [kilA_1] kilA/NOUN
  #   (GLOSS): both of
  #     SOLUTION 2: (kal~A) [kal~A_1] kal~A/INTERJ
  #   (GLOSS): not at all/definitely not

  $analysis =~ s/kilA\/FUNC_WORD/kilA\/NOUN/;
  
	#  SOLUTION 1: ($abaEA) [$abaEA_1] $abaEA/FUNC_WORD
  #   (GLOSS):  + Shabaa + 
     
	#* SOLUTION 1: ($abaEA) [$abaEA_1] $abaEA/NOUN_PROP
  #   (GLOSS): Shabaa
  
  $analysis =~ s/\$abaEA\/FUNC_WORD/\$abaEA\/NOUN_PROP/;
  
#	  SOLUTION 1: (laqad) [qad_1] laqad/FUNC_WORD
 #    (GLOSS):  + indeed (has/have) + 
#* SOLUTION 1: (laqad) [qad_1] laqad/VERB_PART
 #    (GLOSS): indeed (has/have)
#this is ok after changing IN to CC somewhere in the collapse (search for qd)

#  SOLUTION 1: (<il~A) [<il~A_1] <il~A/PART
 #    (GLOSS):  + however/except + 
#* SOLUTION 1: (<il~A) [<il~A_1] <il~A/EXCEPT_PART
 #    (GLOSS): however/except/other
 # SOLUTION 2: (<il~A) [<il~A_2] <il~A/SUB_CONJ
  #   (GLOSS): otherwise/or else

	$analysis =~ s/<il~A\/SUB_CONJ/<il~A\/PART/;
	
#	  SOLUTION 1: (laEal~a) [laEal~a_1] la/EMPHATIC_PARTICLE+Eal~a/FUNC_WORD
#     (GLOSS):  + perhaps + 
#* SOLUTION 1: (laEal~a) [laEal~a_1] laEal~a/SUB_CONJ
#     (GLOSS): perhaps/maybe
	
	$analysis =~ s/la\/EMPHATIC_PARTICLE\+Eal~a\/FUNC_WORD/laEal~a\/SUB_CONJ/;
	
#	  SOLUTION 1: (<iy~AhumA) [<iy~A-_1] <iy~A/FUNC_WORD+humA/PRON_3D
#     (GLOSS):  + to/for/(accus.) + them (both)
#* SOLUTION 1: (<iy~AhumA) [<iy~A_1] <iy~A/PART+humA/PRON_3D
#     (GLOSS): to/for/(accus.) + them (both)
	
	$analysis =~ s/<iy~A\/FUNC_WORD/<iy~A\/PART/;
	
	#  SOLUTION 1: (>ayo) [>ayo_1] >ayo/CONJ
  #   (GLOSS):  + i.e./in other words + 
  #SOLUTION 2: (>ay~) [>ay~_1] >ay~/REL_PRON
  #   (GLOSS):  + any + 
  #SOLUTION 3: (>ay~) [>ay~_1] >ay~/REL_PRON
  #   (GLOSS):  + what/which + 
  #SOLUTION 4: (>ay~) [>ay~_2] >ay~/INTERROG_PART
  #   (GLOSS):  + which + 
  #SOLUTION 5: (>ay) [>ay_1] >ay/ABBREV
  #   (GLOSS):  + A. + 
  #SOLUTION 6: (>ay) [>ay_1] >ay/ABBREV
  #   (GLOSS):  + I. + 

  #SOLUTION 1: (>ayo) [>ayo_1] >ayo/PART
  #   (GLOSS): i.e./or/in other words
  #  SOLUTION 2: (>ay~) [>ay~_1] >ay~/NOUN
  #   (GLOSS): any
  #SOLUTION 14: (>ay~) [>ay~_3] >ay~/INTERROG_PART
  #   (GLOSS): which?
  #SOLUTION 20: (>ay) [>ay_1] >ay/ABBREV
  #   (GLOSS): A.
  #SOLUTION 21: (>ay) [>ay_1] >ay/ABBREV
  #   (GLOSS): I.
  
  $analysis =~ s/>ayo\/CONJ/>ayo\/PART/;
  
  $analysis =~ s/>ay~\/REL_PRON/>ay~\/NOUN/;
  
#    SOLUTION 1: (waEasaY) [EasaY_1] wa/CONJ+EasaY/CONJ
 #    (GLOSS): and + perhaps + 
#* SOLUTION 1: (waEasaY) [EasaY_1] wa/CONJ+EasaY/ADV
 #    (GLOSS): and + perhaps
 
	$analysis =~ s/EasaY\/CONJ/EasaY\/ADV/;
	
#	  SOLUTION 1: (>am~A) [>am~A_1] >am~A/PREP
#     (GLOSS):  + as for/concerning + 
#  SOLUTION 2: (<im~A) [<im~A_1] <im~A/CONJ
#     (GLOSS):  + either + 

#	* SOLUTION 1: (>am~A) [>am~A_1] >am~A/FOCUS_PART
#     (GLOSS): as for/concerning
#  SOLUTION 2: (<im~A) [<im~A_1] <im~A/CONJ
#     (GLOSS): either
#  SOLUTION 3: (>amA) [mA_2] >a/INTERROG_PART+mA/NEG_PART
#     (GLOSS): do/does/did + not

	$analysis =~ s/>am~A\/PREP/>am~A\/FOCUS_PART/;
	
#	  SOLUTION 1: (li*`lika) [li*`lika_1] li*`lika/ADV
#     (GLOSS):  + therefore + 
#  SOLUTION 2: (li*`lika) [*`lika_1] li/PREP+*`lika/DEM_PRON_MS
#     (GLOSS): for/to + that + 

#* SOLUTION 1: (li*`lika) [li*`lika_1] li*`lika/SUB_CONJ
#     (GLOSS): therefore
#  SOLUTION 2: (li*`lika) [*`lika_1] li/PREP+*`lika/DEM_PRON_MS
#     (GLOSS): for/to + that

	$analysis =~ s/li\*\`lika\/ADV/li\*\`lika\/SUB_CONJ/;
	
#	  SOLUTION 1: (h`ka*A) [h`ka*A_1] h`ka*A/CONJ
#     (GLOSS):  + thus/as such + 
#* SOLUTION 1: (h`ka*A) [h`ka*A_1] h`ka*A/ADV
#     (GLOSS): thus/as such

	$analysis =~ s/h\`ka\*A\/CONJ/h\`ka\*A\/ADV/;
	
#	  SOLUTION 1: (ka>an~a) [ka>an~a_1] ka>an~a/CONJ
#     (GLOSS):  + as if + 
#  SOLUTION 1: (ka>an~a) [ka>an~a_1] ka/PREP+>an~a/SUB_CONJ
#     (GLOSS): as + if
	
	$analysis =~ s/ka>an~a\/CONJ/ka\/PREP\+>an~a\/SUB_CONJ/;
	
#  SOLUTION 1: (biHayovu) [Hayovu_1] biHayovu/CONJ
#     (GLOSS):  + where/whereby/since/given that + 
#* SOLUTION 1: (biHayovu) [Hayovu_1] bi/PREP+Hayovu/REL_ADV
#     (GLOSS): with/by + where/whereby/since/given that
	
	$analysis =~ s/biHayovu\/CONJ/bi\/PREP\+Hayovu\/REL_ADV/;
	
#	  SOLUTION 1: (Eam~A) [Eam~A_1] Eam~A/FUNC_WORD
#     (GLOSS):  + as for/regarding + 
#  SOLUTION 2: (Eam~A) [Eam~A_1] Ean/PREP+mA/REL_PRON
#     (GLOSS):  + about what + 
#* SOLUTION 1: (Eam~A) [Eam~A_1] Eam~A/PREP
#     (GLOSS): concerning/regarding
#  SOLUTION 2: (Eam~A) [Eam~A_2] Ean/PREP+mA/REL_PRON
#     (GLOSS): from/about/of + what
	
	$analysis =~ s/Eam~A\/FUNC_WORD/Eam~A\/PREP/;
	
#	  SOLUTION 1: (lam~A) [lam~A_1] lam~A/CONJ ok
#     (GLOSS):  + when/after + 
#  SOLUTION 2: (limA) [limA_1] li/PREP+mA/REL_PRON ok
#     (GLOSS):  + why/for + what + 
#  SOLUTION 3: (lamA) [lamA_1] lamA/NEG_PART
#     (GLOSS):  + (did) not + 

#	* SOLUTION 1: (limA) [limA_1] li/PREP+mA/REL_PRON ok
#     (GLOSS): why/for + what
#  SOLUTION 2: (lamA) [lamA_1] la/RC_PART+mA/NEG_PART
#     (GLOSS): would + not have
#  SOLUTION 3: (lamA) [lamA_2] la/EMPH_PART+mA/NEG_PART
#     (GLOSS): (did) + not
#  SOLUTION 4: (lam~A) [lam~A_1] lam~A/SUB_CONJ ok
#     (GLOSS): when/after
#  SOLUTION 5: (lam~A) [lam~A_2] lam/NEG_PART+mA/NEG_PART
#     (GLOSS): (did) + not

	$analysis =~ s/la\/RC_PART\+mA\/NEG_PART/lamA\/NEG_PART/;
	$analysis =~ s/lam\/NEG_PART\+mA\/NEG_PART/lamA\/NEG_PART/;
	$analysis =~ s/la\/EMPH_PART\+mA\/NEG_PART/lamA\/NEG_PART/;
	
#	 SOLUTION 2: (>ay~atuhA) [>ay~uhA_1] >ay~atuhA/FUNC_WORD
#     (GLOSS):  + O! [voc.fem.] + 

#* SOLUTION 1: (>ay~atuhA) [>ay~uhA_1] >ay~atuhA/PART
#    (GLOSS): oh [voc.fem.]

	$analysis =~ s/>ay~atuhA\/FUNC_WORD/>ay~atuhA\/PART/;
	
#	  SOLUTION 1: (>ay~AF) [>ay~AF_1] >ay~AF/FUNC_WORD
#     (GLOSS):  + whatever/whichever + 
#  SOLUTION 5: (>ay~AF) [>ay~_4] >ay~/REL_PRON+AF/CASE_INDEF_ACC
#     (GLOSS): whatever/whichever/whoever + [acc.indef.]

	$analysis =~ s/>ay~AF\/FUNC_WORD/>ay~\/REL_PRON\+AF\/CASE_INDEF_ACC/;
	
#	  SOLUTION 2: (>ay~uhA) [>ay~uhA_1] >ay~uhA/FUNC_WORD
#     (GLOSS):  + O! [voc.masc.] + 
#* SOLUTION 1: (>ay~uhA) [>ay~uhA_1] >ay~uhA/PART
#     (GLOSS): oh [voc.masc.]

	$analysis =~ s/>ay~uhA\/FUNC_WORD/>ay~uhA\/PART/;
	

	return $analysis; 
}




###########################################3
sub MATCH_TAG($){
	my $tag = shift;
#	VERB_IMPERATIVE           -->  CV
#    VERB_IMPERFECT            -->  IV
#    VERB_IMPERFECT_PASSIVE    -->  IV_PASS
#    VERB_PERFECT              -->  PV
#    VERB_PERFECT_PASSIVE      -->  PV_PASS
#    EMPHATIC_PART             -->  EMPH_PART
#    RESULT_CLAUSE_PARTICLE    -->  RC_PART
#    SUBJUNC                   -->  SUB

#(3) new POS tags have been introduced for more precise tagging:

#    FOCUS_PART  focus particle
#    JUS         jussive prefix (e.
	$tag =~ s/IV_PASS/VERB_IMPERFECT_PASSIVE/;
	$tag =~ s/PV_PASS/VERB_PERFECT_PASSIVE/;
	$tag =~ s/EMPH_PART/EMPHATIC_PART/;
	$tag =~ s/RC_PART/RESULT_CLAUSE_PARTICLE/;
	$tag =~ s/^SUB$/SUBJUNC/;
	$tag =~ s/^SUB\+/SUBJUNC\+/;
	$tag =~ s/IV\+/VERB_IMPERFECT\+/;
	$tag =~ s/CV\+/VERB_IMPERATIVE\+/;
	$tag =~ s/PV\+/VERB_PERFECT\+/;
	$tag =~ s/^FOCUS_PART$/PREP/;
	
	$tag =~ s/^JUS$/SUBJUNC/;
	$tag =~ s/SUB_CONJ/CONJ/;	#well this might be confusing, but this is what we have!
	$tag =~ s/FUNC_WORD/CONJ/;
	#buckv1.0:EndmA	(CONJ EinodamA)
	#atb1v3.0:EndmA	(SUB_CONJ EinodamA)
	#buckv1.0:(FUNC_WORD >an~a)
	#atb1v3.0:(SUB_CONJ >an~a)	
	
	#$tag =~ s/_ACC$/_ACCGEN/;
	#$tag =~ s/_GEN$/_ACCGEN/;
	#buckv1.0:lE$ryn	(PREP li) ([Eu$or_1]+NOUN+NSUFF_MASC_DU_ACCGEN Eu$or+ayoni)
	#atb1v3.0:lE$ryn	(PREP li) ([Ei$oruwn_1]+NUM+NSUFF_MASC_PL_GEN Ei$or+iyna)
	
	$tag =~ s/EXCEPT_PART/PART/;
	#buckv1.0:AlA   (PART <il~A)
	#atb1v3.0:AlA	(EXCEPT_PART <il~A)
	
	#$tag =~ s/PREP/CONJ/;
	#buckv1.0:mn*	(CONJ muno*u)
	#atb1v3.0:mn*	(PREP muno*u)
	#it looks more like a preposition, so there might have been a mistake in buckv1,
	#also in atb1v2 it is considered as a prep.
	
	#atb1v3:ATArA		[<iTAr_1]	<iTAr/NOUN+AF/CASE_INDEF_ACC
	#buckv1.0:(<iTArAF) [<iTAr_1] <iTAr/NOUN+AF/NSUFF_MASC_SG_ACC_INDEF
	$tag =~ s/NSUFF_MASC_SG_ACC_INDEF/CASE_INDEF_ACC/;
	
	return $tag;
}
	
	
#####################################
sub GET_VOWELS_PATTERN($){
	
	my $morph = shift @_;
	#if there is a consonant followed by no vowel nor a "long vowel=wyA"
	#then it's foreign word!
	if ($morph =~ /[^aiueo~`FNK+Ayw][^aiueo~`FNKAyw+]/){		
		return "NOP";
	}
	#remove li
	$morph =~ s/li\+//;
	#remove Al
	$morph =~ s/Al\+//;
	#remove ap
	$morph =~ s/\+ap//;
	#remove At
	$morph =~ s/\+At//;
	#remove case
	$morph =~ s/\+[uia]$//;
	#remove case
	$morph =~ s/\+t[uia]$//;
	
	
	$morph =~ s/\+//g;
	$morph =~ s/[^aiueo~`FNK]/c/g;
	return $morph;
}

	
####################################3
our @SIGTAGS = ('ABBREV',
			   'NOUN',
			   #'REL_ADV','REL_PRON',
			   'NOUN_PROP',
			   'ADJ',
			   'ADV',
			   'VERB_IMPERFECT',
			   'NEG_PART\+PVSUFF_SUBJ',
			   'VERB_PASSIVE',
			   'VERB_IMPERFECT_PASSIVE',
			   'VERB_PERFECT',
			   'VERB_IMPERATIVE',
			   'NUM'
			   
			  );
			   
			   
our @SIGTAGSCOLL = ('NN',
				   'NNS',
				   #'WRB', 'WP', #?
				   'NNP',
				   'NNPS',
				   'JJ',
				   'RB', #ADV
				   'VBP',
				   'VBN',
				   'VBD',
				   'VB',
				   'CD'
				  );


our @FUNCTAGS = ('CONJ',
				'DEM_PRON',
				'DET',
				'NEG_PART',
				'EMPHATIC_PART',
				'EXCEPT_PART',
				'INTERROG_PART',
				'RESULT_CLAUSE_PARTICLE',
				'SUBJUNC',
				'FUT_PART',
				'PREP',
				'VERB_PART',
				'FUNC_WORD',
				'SUB_CONJ',
				'INTERJ',
				'CVSUFF_DO',
				'IVSUFF_DO',
				'PVSUFF_DO',
				'POSS_PRON'
			   );

our @FUNCTAGSCOLL = ('CC',
					'DT',
					'RP',
					'IN',
					'UH',
					'PRP',
					'PRPS'
				   );

#########################################################
sub READ_MAP($){
	my $file = shift @_;
	my @wordanal = ();
	
	while(($_=<$file>)!~/^\s*\<s\>\s*\<\/s\>\s*$/ and $_){
		my $word = ""; my $rest = "";
		if(/^\s*(\S+)\s+/){
			$word = $1;
			$rest = $';
		}
		else{die "unexpected format\n";}
		
		my $wordanal = WordAnal->new();
		$wordanal->word($word);
		@{$wordanal->analyses} = ();
		while($rest=~/^\s*(\S+)\s+[0-9.e-]+\s*/){
			$rest = $';
			push @{$wordanal->analyses}, $1;			
		}
		
		push @wordanal, $wordanal;
	}
	
	return @wordanal;
}

#########################################################


#########################################################
sub READ_CORPUS($){
	my $file = shift @_;
	my @wordanal = ();
	
	while(($_=<$file>)!~/^\{sentence \#\d+\}\s*$/ and $_){
		chop;
		
		my ($coword,$cosol) = ("","");
		if (/^\s+(\S+)\s+(\(.+\))\s*$/){
			($coword,$cosol) = ($1,$2);
		}
		else{
			#in atb2, there are letters recognized as arabic words from \xF6
			#in the treebank were annotated as (NO_FUNC _), i change to PUNC
			($coword,$cosol) = ("_","(PUNC ppUS)");
		}
		
		
	
		my $wordanal = WordAnal->new();
		$wordanal->word($coword);
		push @{$wordanal->analyses}, $cosol;
		
		push @wordanal, $wordanal;
	}
	
	return @wordanal;
}

#########################################################


sub READ_ANALYSES($){
	my $file = shift @_;
	my @wordanal = ();
	$_ = <$file>;
	
	chop; my $word = $_; 
	
	#changed $word to defined($word) for oov-ooc, if it doesn't work somewhere else
	#i'll need better solution
	while(defined($word) and $word!~/^#\s*$/){	
		my $wordanal = WordAnal->new();
		$wordanal->word($word);
		@{$wordanal->analyses} = ();
		my $line = "";
		while(($line=<$file>)=~/^\s+(\(.+\))/){
			#might have __SVM__, or __XXX__
			#remove trailing spaces
			$line = $1.$';
			if ($line =~ /\s+$/){
				$line = $`;
			}
			
			push @{$wordanal->analyses}, $line;
		}
		
		chop $line; $word = $line; 

		push @wordanal, $wordanal;
	}
	
	return @wordanal;
}



################################################
sub REMOVE_VOWELS {
	my ($wordr) = @_;
	#$wordr = REMOVEMARKSWORD($wordr);
	return $wordr if (not $wordr);
	
	$wordr =~ s/[aiueo~`FNK+_]//g;
	
	return $wordr;
}


################################################
sub REMOVEMARKSPUNC {
	my ($wordr) = @_;
	#$wordr = REMOVEMARKSWORD($wordr);
	return $wordr if (not $wordr);
	
	$wordr = HEX_TO_CHAR($wordr);
	#$wordr =~ s/\.\.\./ppTPERIOD/g;
	#$wordr =~ s/\.\./ppDPERIOD/g;
	#$wordr =~ s/\./ppPERIOD/g;
	#$wordr =~ s/\,/ppCOMMA/g;
	#$wordr =~ s/\-/ppDASH/g;
	#$wordr =~ s/\;/ppSCM/g;
	#$wordr =~ s/\:/ppCOLON/g;
	$wordr =~ s/\\/ppSLASH/g;
	$wordr =~ s/\//ppBSM/g;
	#$wordr =~ s/\"/ppQUOT/g;
	#$wordr =~ s/\%/ppPERCM/g;
	#$wordr =~ s/\?/ppQM/g;
	#$wordr =~ s/\!/ppEM/g;
	$wordr =~ s/\(/ppLRB/g;
	$wordr =~ s/\)/ppRRB/g;
	$wordr =~ s/\+/ppPLUS/g;
	#$wordr =~ s/\&/ppAND/g;
	#$wordr =~ s/\>/ppBT/g;
	#$wordr =~ s/\</ppST/g;
	#$wordr =~ s/\$/ppDOLLAR/g;
	#$wordr =~ s/\*/ppSTAR/g;
	#$wordr =~ s/\_/ppUS/g;	#Under Score
	$wordr =~ s/\{/ppLCP/g;
	$wordr =~ s/\{/ppRCP/g;
	
	return $wordr;
}


sub REMOVEMARKSWORD {
	my ($wordr) = @_;
	return $wordr if (not $wordr);

	$wordr =~ s/\</I/g;	#alef with hamza below
	$wordr =~ s/\>/O/g;	#alef with hamza above
	$wordr =~ s/I/A/g;	#change back to A
	$wordr =~ s/O/A/g;	#change back to A
	
	$wordr =~ s/\&/W/g;	#waw with hamza above
	$wordr =~ s/\}/U/g;	#yaa with hamza above
	$wordr =~ s/\{/X/g;	#uknown, doesn't appear in the new transliteration
	$wordr =~ s/X/A/g;  #it's actually alef
	$wordr =~ s/\|/M/g;	#alef Mamdoda
	$wordr =~ s/M/A/g;	#change back to A to avoid segmentation problems
	$wordr =~ s/\'/B/g;	#hamza 
	$wordr =~ s/\$/C/g;	#shen
	$wordr =~ s/\*/L/g;	#thaL :)
	$wordr =~ s/\xF0/r/g;	#atb3 analyses generated this letter, in utf8 it's a non-character...
	$wordr =~ s/\xDC/_/g; #error in atb1 seems that _ was treated as arabic word! [TODO, not tried if this corrects problem]
	#$wordr =~ s/\_//g;	#appears in atb3, it's a word which includes charachters to widen letters, like slA__m
	
	#$wordr =~ s/\//ppSLASH/g;
	#$wordr =~ s/\\/ppBSM/g;
	#$wordr =~ s/\"/ppQUOT/g;
	#$wordr =~ s/\%/ppPERCM/g;
	
	return $wordr;
}

#################################################################
sub IS_EQUAL_ARAB{
	my ($word1,$word2) = @_;
	return 1 if (not $word1 and not $word2);

	$word1 = DEF_FORMAT($word1);
	$word2 = DEF_FORMAT($word2);
	$word1 = REMOVEMARKSWORD($word1);
	$word2 = REMOVEMARKSWORD($word2);
	$word1 =~ s/[aiueo~`FNK+]//g;
	$word2 =~ s/[aiueo~`FNK+]//g;
	my @word1 = split("",$word1);
	my @word2 = split("",$word2);
	my ($i,$j) = (0,0);
	for (;$i<@word1 and $j<@word2;$i++,$j++){
		 next if ($word1[$i] eq $word2[$j]);
		 next if (($word1[$i] eq "p" and $word2[$j] eq "t")
				  or ($word1[$i] eq "t" and $word2[$j] eq "p"));
		 next if (($word1[$i] eq "p" and $word2[$j] eq "h")
				  or ($word1[$i] eq "h" and $word2[$j] eq "p"));
		 next if (($word1[$i] eq "y" and $word2[$j] eq "A")
				  or ($word1[$i] eq "A" and $word2[$j] eq "y"));
		 next if (($word1[$i] eq "V" and $word2[$j] eq "f")
				  or ($word1[$i] eq "f" and $word2[$j] eq "V"));
		 #i think the following is a mistake in atb2-with-vowel
		 #(CONJ wa-) (S (VP (NOUN -<HAltjm) should be w<HAlthm
		 next if (($word1[$i] eq "h" and $word2[$j] eq "j")
				  or ($word1[$i] eq "j" and $word2[$j] eq "h"));
		 #atb2: l>lA - lUlA
		 next if (($word1[$i] eq "A" and $word2[$j] eq "U")
				  or ($word1[$i] eq "U" and $word2[$j] eq "A"));
		 next if (($word1[$i] eq ":" and $word2[$j] eq ",")
				  or ($word1[$i] eq "," and $word2[$j] eq ":"));
		 
		 #DwB amd DW
		 $j++ and next if ($word1[$i] eq "W" and $word2[$j] eq "w" and $j+1<@word2 and $word2[$j+1] eq "B");
		 $i++ and next if ($word2[$j] eq "W" and $word1[$i] eq "w" and $i+1<@word1 and $word1[$i+1] eq "B");
		 
		 #CU and CyB
		 $j++ and next if ($word1[$i] eq "U" and $word2[$j] eq "y" and $j+1<@word2 and $word2[$j+1] eq "B");
		 $i++ and next if ($word2[$j] eq "U" and $word1[$i] eq "y" and $i+1<@word1 and $word1[$i+1] eq "B");

		 #y can be skipped especially in latin words
		 $j-- and next if ($word1[$i] eq "y" and $word2[$j] ne "y");
		 $i-- and next if ($word1[$i] ne "y" and $word2[$j] eq "y");
		 
		 return 0;
	}
	
	if ($i<@word1 or $j<@word2) {return 0};
	
	return 1;
}


#################################################################

#make all the formats the same so we can match
sub DEF_FORMAT{
	my ($word) = @_;
	return $word if (not $word);

	$word =~ s/Y'/\}/g;	
	$word =~ s/YB/\}/g;	
	$word =~ s/y'/\}/g;	
	$word =~ s/w'/\&/g;
	$word =~ s/ll/lAl/g; #g was added because of cases like lAlhlAl :)
	$word =~ s/AnlA/AlA/;
	$word =~ s/mnm/mm/;
	$word =~ s/nm/m/;
	$word =~ s/nn/n/;
	#$word =~ s/knnA/knA/;
	$word =~ s/\{/A/g;	
	$word =~ s/Y/y/g;
	$word =~ s/\</A/g;	
	$word =~ s/\>/A/g;	
	
	$word = HEX_TO_CHAR($word);
	return $word;
}


############################################
sub HEX_TO_CHAR($){
	my $word = shift;
	return $word if (not $word);
	$word =~ s/\&gt\;/\>/g;
	$word =~ s/\xA1/\,/g;	
	$word =~ s/\xD8\x8C/\,/g;
	$word =~ s/\xBF/\?/g;
	#$word =~ s/\x1F\x06/\?/g;
	$word =~ s/\xF6/\_/g;	#atb2
	$word =~ s/\xD8\x9F/\?/g;
	$word =~ s/\xDC/\_/g;
	$word =~ s/\xD9\x80/\_/g;
	$word =~ s/\xD9\x8B/\_/g;
	$word =~ s/\xF0/\_/g;	#atb2
	return $word;
}





###########################################3


sub PERFORM_AUTO_SEP{
	my ($line,$tagmorphs,$whichatb) = @_;
	
	my $num_parts = 0;
	$line ='+'.$line.'+';
	my @tags = ($line =~ /\/([^\/]+?)\+/g);	#match tags which comes after /
	my @morphs = ($line =~ /\+(.+?)\//g);
	print STDERR "num tags!= num morphs: $line\n" and exit if (@tags != @morphs);
	
	my $size = @tags; my $last = "";
	for (my $j=$size-1; $j>=0; $j--){
		if ($tags[$j]=~/^PVSUFF_[^D]/){# and $last ne "PVSUFF"){
			print STDERR "PVSUFF at the begin of: $line\n" and exit if $j==0;
			$tags[$j-1] .= "+$tags[$j]";
			$morphs[$j-1] .= "+$morphs[$j]";
			delete $tags[$j];
			delete $morphs[$j];
			$last = "PVSUFF";
		}
		elsif ($tags[$j]=~/^IVSUFF_[^D]/ and $last ne "IVSUFF"){
			print STDERR "IVSUFF at the begin of: $line\n" and exit if $j==0;
			$tags[$j-1] .= "+$tags[$j]";
			$morphs[$j-1] .= "+$morphs[$j]";
			delete $tags[$j];
			delete $morphs[$j];
			$last = "IVSUFF";
		}
		elsif ($tags[$j]=~/^CVSUFF_[^D]/ and $last ne "CVSUFF"){	#atb2 only
			print STDERR "CVSUFF at the begin of: $line\n" and exit if $j==0;
			$tags[$j-1] .= "+$tags[$j]";
			$morphs[$j-1] .= "+$morphs[$j]";
			delete $tags[$j];
			delete $morphs[$j];
			$last = "CVSUFF";
		}
		elsif ($tags[$j]=~/^NSUFF/ and $last ne "NSUFF"){
			print STDERR "NSUFF at the begin of: $line\n" and exit if $j==0;
			$tags[$j-1] .= "+$tags[$j]";
			$morphs[$j-1] .= "+$morphs[$j]";
			delete $tags[$j];
			delete $morphs[$j];
			$last = "NSUFF";
		}
		elsif ($tags[$j]=~/^CASE/ and $last ne "CASE"){ #atb2 only doesn't appear in atb1
			print STDERR "CASE at the begin of: $line\n" and exit if $j==0;
			$tags[$j-1] .= "+$tags[$j]";
			$morphs[$j-1] .= "+$morphs[$j]";
			delete $tags[$j];
			delete $morphs[$j];
			$last = "CASE";
		}#the following comes before
		elsif ($tags[$j] eq "DET" and $last ne "DET"){
			next if $j==@tags-1;
			$tags[$j] .= "+".$tags[$j+1];
			$morphs[$j] .= "+".$morphs[$j+1];
			delete $tags[$j+1];
			delete $morphs[$j+1];
			$last = "DET";
		}
		elsif ($tags[$j]=~/^IV\d/ and $last ne "IVn"){
			print STDERR "IV[1-3] no one after: $line\n" and exit if $j==@tags-1;
			$tags[$j] .= "+".$tags[$j+1];
			$morphs[$j] .= "+".$morphs[$j+1];
			delete $tags[$j+1];
			delete $morphs[$j+1];
			$last = "IVn";
		}
		elsif ($tags[$j] eq "FUT" and $last ne "FUT"){
			print STDERR "FUT no one after: $line\n" and exit if $j==@tags-1;
			$tags[$j] .= "+".$tags[$j+1];
			$morphs[$j] .= "+".$morphs[$j+1];
			delete $tags[$j+1];
			delete $morphs[$j+1];
			$last = "FUT";
		}
		#this is seperated in the treebank of atb1v3, so i'll ignore it by setting whichatb=1
		#in atb2 it's SUB_CONJ seperated
		#in atb3 it's SUB (like atb1v3) but i don't have seperated format in atb3, so i assume it was treated like atb1v3
		#SUB will be changed by seperate-clitics to SUBJUNC
		#also SUB_CONJ should be changed to SUBJUNC
		#SUB_CONJ is used in atb1v3 as FUNC_WORD in atb1
		#6.12.07.19.22
		#taken out, i want it to be seperated
		#elsif ( ($tags[$j] eq "SUBJUNC" or $tags[$j] eq "SUB") 
			#   and ($whichatb == 2 or $whichatb == 3) and $last ne "SUBJUNC"){ #atb2 only
			#6.12.07.19.16
			#there is no connection to the part, just seperate SUBJUNC which appears also in buckout
			#   and $last ne "SUBJUNC"){ #atb2 only
			#print STDERR "SUBJUNC no one after: $line\n" and exit if $j==@tags-1;
			#$tags[$j] .= "+".$tags[$j+1];
			#$morphs[$j] .= "+".$morphs[$j+1];
			#delete $tags[$j+1];
			#delete $morphs[$j+1];
			#$last = "SUBJUNC";
		#}
	}
	
	for(my ($i,$j)=(0,0); $i<@tags; $i++){		
		@$tagmorphs[$j++] = "($tags[$i] $morphs[$i])" if defined($tags[$i]);
	}
}


our %COLLAPSEHASH = (
				#"NO\_FUNC" => "NNP",
				"NON\_ARABIC" => "FW",
				#" \\\)/"PUNC \\\)/g;
				#" \/\)/"PUNC \/\)/g;
				"ABBREV" => "NN",
				"DET+ABBREV" => "NN",
				"LATIN" => "FW",
				"DET\+NOUN" => "NN",
				"DET\+NOUN\+NSUFF\_FEM\_SG" => "NN",
				"NOUN" => "NN",
				"NOUN_MS" => "NN",	#new
				"NOUN_MP" => "NN",	#new
				"NOUN\+NSUFF\_FEM\_SG" => "NN",
				"NOUN\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "NN",
				"DEM\+NOUN" => "NN",
				"DET\+NOUN\+CASE\_DEF\_ACC" => "NN",
				"DET\+NOUN\+CASE\_DEF\_GEN" => "NN",
				"DET\+NOUN\+CASE\_DEF\_NOM" => "NN",
				"DET\+NOUN\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "NN",
				"DET\+NOUN\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "NN",
				"DET\+NOUN\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "NN",
				"NOUN\+CASE\_DEF\_ACC" => "NN",
				"NOUN\+CASE\_DEF\_GEN" => "NN",
				"NOUN\+CASE\_DEF\_NOM" => "NN",
				"NOUN\+CASE\_INDEF\_ACC" => "NN",
				"NOUN\+CASE\_INDEF\_GEN" => "NN",
				"NOUN\+CASE\_INDEF\_NOM" => "NN",
				"NOUN\+NSUFF\_FRM\_SG\+CASE\_DEF\_ACC" => "NN",
				"NOUN\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "NN",
				"NOUN\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "NN",
				"NOUN\+NSUFF\_FEM\_SG\+CASE\_INDEF\_ACC" => "NN",
				"NOUN\+NSUFF\_FEM\_SG\+CASE\_INDEF\_GEN" => "NN",
				"NOUN\+NSUFF\_FEM\_SG\+CASE\_INDEF\_NOM" => "NN",
				"NEG\_PART\+NOUN" => "NN",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_ACCGEN" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_ACC" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_GEN" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_NOM" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_ACC_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_GEN_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_DU\_NOM_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_PL" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_ACCGEN" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_ACC" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_GEN" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_NOM" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_ACC_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_GEN_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_DU\_NOM_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_ACCGEN" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_ACC" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_GEN" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_NOM" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_ACC_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_GEN_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_MASC\_PL\_NOM_POSS" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_ACCGEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_ACC" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_ACC_POSS" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_GEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_GEN_POSS" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_ACCGEN\_POSS" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_NOM" => "NNS",
				"NOUN\+NSUFF\_FEM\_DU\_NOM\_POSS" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_ACCGEN" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_ACC" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_GEN" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_ACCGEN\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_ACC\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_GEN\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_NOM" => "NNS",
				"NOUN\+NSUFF\_MASC\_DU\_NOM\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_ACCGEN" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_ACC" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_GEN" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_ACCGEN\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_ACC\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_GEN\_POSS" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_NOM" => "NNS",
				"NOUN\+NSUFF\_MASC\_PL\_NOM\_POSS" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACCGEN" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_NOM" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACC" => "NNS",
				"DET\+NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_GEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACCGEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_NOM" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_INDEF\_ACCGEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACC" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_DEF\_GEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_INDEF\_ACC" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_INDEF\_GEN" => "NNS",
				"NOUN\+NSUFF\_FEM\_PL\+CASE\_INDEF\_NOM" => "NNS",
				"DET\+NOUN\_PROP" => "NNP",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_SG" => "NNP",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "NNP",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "NNP",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "NNP",
				"NOUN\_PROP" => "NNP",
				"NOUN\_PROP\+NSUFF\_FEM\_SG" => "NNP",
				"NOUN\_PROP\+NSUFF\_MASC\_DU\_NOM\_POSS" => "NNPS",	#new
				"NOUN_PROP+NSUFF_MASC_DU_NOM" => "NNPS",	#new
				"NOUN_PROP+NSUFF_FEM_DU_ACCGEN_POSS" => "NNPS", #new
				"NOUN_PROP+NSUFF_FEM_DU_GEN_POSS" => "NNPS", #new
				"NOUN_PROP+NSUFF_FEM_DU_ACC_POSS" => "NNPS", #new
				"NOUN_PROP+NSUFF_FEM_DU_NOM_POSS" => "NNPS", #new
				"NOUN_PROP+NSUFF_FEM_DU_NOM" => "NNPS", #buckv1.0 over atb3
				"NOUN_PROP+NSUFF_MASC_DU_ACCGEN_POSS" => "NNPS",	#new
				"NOUN_PROP+NSUFF_MASC_DU_ACCGEN" => "NNPS", #new
				"NOUN_PROP+NSUFF_FEM_DU_ACCGEN" => "NNPS", #new
				"NOUN\_PROP\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "NNP",
				"NOUN\_PROP\+CASE\_DEF\_ACC" => "NNP",
				"NOUN\_PROP\+CASE\_DEF\_GEN" => "NNP",
				"NOUN\_PROP\+CASE\_DEF\_NOM" => "NNP",
				"NOUN\_PROP\+CASE\_INDEF\_GEN" => "NNP",
				"NOUN\_PROP\+CASE\_INDEF\_NOM" => "NNP",
				"NOUN\_PROP\+CASE\_INDEF\_ACC" => "NNP",
				"NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "NNP",
				"NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "NNP",
				"NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "NNP",
				"NOUN\_PROP\+NSUFF\_FEM\_SG\+CASE\_INDEF\_GEN" => "NNP",
				"NOUN_PROP+NSUFF_FEM_SG+CASE_INDEF_NOM" => "NNP", #atb3
				"NOUN_PROP+NSUFF_FEM_SG+CASE_INDEF_ACC" => "NNP", #atb3
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_DU" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_DU_ACCGEN" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_DU_ACC" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_DU_GEN" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_DU_NOM" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_PL" => "NNPS",
				"DET+NOUN_PROP+NSUFF_FEM_PL+CASE_DEF_GEN" => "NNPS", #atb3
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_DU\_ACCGEN" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_DU\_GEN" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_DU\_ACC" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_DU\_NOM" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_PL\_ACCGEN" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_PL\_ACC" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_PL\_GEN" => "NNPS",
				"DET\+NOUN\_PROP\+NSUFF\_MASC\_PL\_NOM" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_NOM" => "NNPS",	#added
				"NOUN\_PROP\+NSUFF\_FEM\_PL" => "NNPS",
				"NOUN\_PROP\+NSUFF\_FEM\_PL\+CASE\_INDEF\_ACCGEN" => "NNPS",
				"NOUN_PROP+NSUFF_FEM_PL+CASE_DEF_GEN" => "NNPS", #atb3
				"NOUN_PROP+NSUFF_FEM_PL+CASE_INDEF_GEN" => "NNPS", #atb3
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_ACCGEN" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_GEN" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_ACC" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_NOM" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_GEN_POSS" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_ACC_POSS" => "NNPS",
				"NOUN\_PROP\+NSUFF\_MASC\_PL\_NOM_POSS" => "NNPS",
				"DET\+NOUN\_PROP\+CASE\_DEF\_ACC" => "NNP",
				"DET\+NOUN\_PROP\+CASE\_DEF\_GEN" => "NNP",
				"DET\+NOUN\_PROP\+CASE\_DEF\_NOM" => "NNP",
				"DET\+NOUN\_PROP\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACCGEN" => "NNPS",
				"ADJ" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_ACCGEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_ACC" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_GEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_NOM" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_ACCGEN\_POSS" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_ACC\_POSS" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_GEN\_POSS" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_NOM\_POSS" => "JJ",
				"ADJ\+NSUFF\_FEM\_DU\_NOM" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_ACCGEN" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_ACC" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_GEN" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_ACCGEN\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_ACC\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_GEN\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_NOM" => "JJ",
				"ADJ\+NSUFF\_MASC\_DU\_NOM\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_ACCGEN" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_ACC" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_GEN" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_ACCGEN\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_ACC\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_GEN\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_NOM\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_NOM" => "JJ",
				"ADJ\+NSUFF\_MASC\_PL\_NOM\_POSS" => "JJ",
				"ADJ\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "JJ",
				"ADJ\_PROP" => "JJ",
				"ADJ\_PROP\+NSUFF\_FEM\_SG" => "JJ",
				"ADJ\_PROP\+NSUFF\_MASC\_PL\_NOM" => "JJ",
				"ADJ\_PROP\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "JJ",
				"DET\+ADJ" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_DU\_ACCGEN" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_DU\_ACCGEN_POSS" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_DU\_ACC" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_DU\_GEN" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_DU\_NOM" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_PL" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_SG" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_DU\_ACCGEN" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_DU\_ACCGEN_POSS" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_DU\_ACC" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_DU\_GEN" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_DU\_NOM" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_ACCGEN" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_GEN" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_ACC" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_NOM" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_GEN_POSS" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_ACC_POSS" => "JJ",
				"DET\+ADJ\+NSUFF\_MASC\_PL\_NOM_POSS" => "JJ",
				"DET\+ADJ\_PROP" => "JJ",
				"DET\+ADJ\_PROP\+NSUFF\_FEM\_SG" => "JJ",
				"DET\+ADJ\_PROP\+NSUFF\_MASC\_PL\_ACCGEN" => "JJ",
				"DET\+ADJ\_PROP\+NSUFF\_MASC\_PL\_ACC" => "JJ",
				"DET\+ADJ\_PROP\+NSUFF\_MASC\_PL\_GEN" => "JJ",
				"ADJ\+CASE\_DEF\_ACC" => "JJ",
				"ADJ\+CASE\_DEF\_GEN" => "JJ",
				"ADJ\+CASE\_DEF\_NOM" => "JJ",
				"ADJ\+CASE\_INDEF\_ACC" => "JJ",
				"ADJ\+CASE\_INDEF\_GEN" => "JJ",
				"ADJ\+CASE\_INDEF\_NOM" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG\+CASE\_INDEF\_ACC" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG\+CASE\_INDEF\_GEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_SG\+CASE\_INDEF\_NOM" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACCGEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACC" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_GEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_NOM" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_INDEF\_ACCGEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_INDEF\_GEN" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_INDEF\_ACC" => "JJ",
				"ADJ\+NSUFF\_FEM\_PL\+CASE\_INDEF\_NOM" => "JJ",
				"DET\+ADJ" => "JJ",
				"DET\+ADJ\+CASE\_DEF\_ACC" => "JJ",
				"DET\+ADJ\+CASE\_DEF\_GEN" => "JJ",
				"DET\+ADJ\+CASE\_DEF\_NOM" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACCGEN" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACC" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_GEN" => "JJ",
				"DET\+ADJ\+NSUFF\_FEM\_PL\+CASE\_DEF\_NOM" => "JJ",
				"ADV" => "RB",
				"DET+ADV" => "RB", #new
				"ADV\+NSUFF\_FEM\_SG" => "RB",
				"ADV\+NSUFF\_MASC\_DU\_NOM\_POSS" => "RB", #new
				"ADV+NSUFF_MASC_DU_NOM" => "RB", #buckv1.0 over atb3
				"ADV+NSUFF_FEM_DU_ACCGEN" => "RB", #buckv1.0 over atb3
				"ADV+NSUFF_MASC_DU_ACCGEN" => "RB", #new buckv1.0!
				"ADV+NSUFF_MASC_PL_ACCGEN" => "RB", #new buckv1.0!
				"ADV+NSUFF_MASC_PL_NOM" => "RB", #new buckv1.0
				"ADV\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "RB",
				"DET\+ADV\+NSUFF\_FEM\_SG" => "RB",
				"DET+ADV+NSUFF_MASC_DU_ACCGEN" => "RB", #buckv1.0 over atb3
				"DET+ADV+NSUFF_MASC_PL_ACCGEN" => "RB", #buckv1.0 over atb3
				"ADV\+CASE\_DEF\_ACC" => "RB",
				"ADV\+CASE\_INDEF\_ACC" => "RB",
				"CONJ" => "CC",
				"DEM\_PRON\_F" => "DT",
				"DEM\_PRON\_FD" => "DT",
				"DEM\_PRON\_FS" => "DT",
				"DEM\_PRON\_MD" => "DT",
				"DEM\_PRON\_MP" => "DT",
				"DEM\_PRON\_MS" => "DT",
				"DEM\_PRON\_MP\+CASE\_DEF\_GEN" => "DT",
				"DET" => "DT",
				"DET\+NEG\_PART" => "RP",
				"DET+NEG_PART+CASE_DEF_GEN" => "RP", #atb3
				"DET\+PREP" => "IN",
				"EMPHATIC\_PARTICLE" => "RP",
				"EMPHATIC\_PART" => "RP",
				"EXCEPT\_PART" => "RP",
				"INTERROG\_PART" => "RP",
				"INTERROG_PART+CASE_DEF_GEN" => "RP", #atb3
				"INTERROG_PART+CASE_DEF_NOM" => "RP", #atb3
				"INTERROG_PART+NSUFF_FEM_SG+CASE_DEF_GEN" => "RP", #atb3
				"NEG\_PART" => "RP",
				"NEG\_PART\+CASE\_DEF\_GEN" => "RP",
				"NEG\_PART\+CASE\_DEF\_NOM" => "RP",
				"NEG\_PART\+CASE\_DEF\_ACC" => "RP",
				"NEG\_PART\+PVSUFF\_SUBJ\:3MS" => "RP",
				"NEG_PART+PVSUFF_SUBJ:3FD" => "RP", #new  buckv1.0
				"NEG_PART+PVSUFF_SUBJ:3MD" => "RP", #buckv1.0 over atb3
				"PART" => "RP",
				"RESULT\_CLAUSE\_PARTICLE" => "RP",
				"SUBJUNC" => "RP",
				"VERB\_PART" => "CC", #RP changed to CC (FUNC_WORD qd), (VERB_PART qd) (FUNC_WORD -> CONJ)
				"FUT\_PART" => "RP",
				"INTERROG\_PART\+NEG\_PART" => "RP", #SOLUTION 3: (>amA) [mA_2] >a/INTERROG_PART+mA/NEG_PART atb1v3
				"INTERROG\_PART\+NEG\_PART\+PVSUFF\_SUBJ\:3FS" => "RP",
				"INTERROG\_PART\+NEG\_PART\+PVSUFF\_SUBJ\:3MS" => "RP",
				"FUNC\_WORD" => "CC",	#IN changed to CC to match buckwalter of atb2 (where An is SUB_CONJ)
				"PREP" => "IN",
				"PREP\+NSUFF\_FEM\_SG" => "IN",
				"PREP\+NSUFF\_FEM\_SG+CASE_DEF_ACC" => "IN",
				"PREP\+NSUFF\_FEM\_SG+CASE_DEF_GEN" => "IN",
				"PREP\+NSUFF\_FEM\_SG+CASE_DEF_NOM" => "IN",
				"PREP\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "IN",
				"PREP\_PROP" => "IN",
				"SUB\_CONJ" => "CC",	#was IN changed to CC to match buckwalter of atb2
				"SUB\_CONJ\+NEG\_PART" => "RP",
				"PREP\+PRON\_3MP" => "IN",
				"SUB\_CONJ\+PRON\_3MP" => "CC",
				"FUT\+IV1P\+VERB\_IMPERFECT" => "VBP",
				"FUT\+IV1S\+VERB\_IMPERFECT" => "VBP",
				"FUT\+IV2MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBP",
				"FUT\+IV2MS\+VERB\_IMPERFECT" => "VBP",
				"FUT\+IV3FS\+VERB\_IMPERFECT" => "VBP",
				"FUT\+IV3MD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBP",
				"FUT\+IV3MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBP",
				"FUT+IV3MP+VERB_IMPERFECT+IVSUFF_SUBJ:MP_MOOD:SJ" => "VBP", #buckv1.0 over atb3
				"FUT\+IV1P\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"FUT\+IV1S\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"FUT\+IV2D\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBP",
				"FUT\+IV2MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBP",
				"FUT\+IV2MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"FUT\+IV3FD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBP",
				"FUT\+IV3FS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"FUT\+IV2FS\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:2FS\_MOOD\:SJ" => "VBP", #new
				"FUT\+IV2FP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:FP" => "VBP", #new
				"FUT\+IV3FP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:FP" => "VBP", #new
				"FUT\+IV3MD\+VERB\_IMPERFECT\+IVSUFF_SUBJ\:D\_MOOD\:SJ" => "VBP",	#new
				"FUT+IV2D+VERB_IMPERFECT+IVSUFF_SUBJ:D_MOOD:SJ" => "VBP", #new
				"FUT+IV3FD+VERB_IMPERFECT+IVSUFF_SUBJ:D_MOOD:SJ" => "VBP", #new
				"FUT\+IV3MS\+VERB\_IMPERFECT" => "VBP",
				"IV1P\+VERB\_IMPERFECT" => "VBP",
				"IV1P\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"IV1P\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"IV1P\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:J" => "VBP",
				"IV1S\+VERB\_IMPERFECT" => "VBP",
				"IV1S\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"IV1S\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"IV1S\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:J" => "VBP",
				"IV1S\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBP",
				"IV1S\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBP",
				"IV2D\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBP",
				"IV2D\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:SJ" => "VBP",	#new
				"IV2FP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:FP" => "VBP",
				"IV2FS\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:2FS\_MOOD\:SJ" => "VBP",
				"IV2FS\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:2FS\_MOOD\:I" => "VBP",	#new
				"IV2MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBP",
				"IV2MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:SJ" => "VBP",
				"IV2MS\+VERB\_IMPERFECT" => "VBP",
				"IV2MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"IV2MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"IV2MS+VERB\_IMPERFECT+IVSUFF_MOOD:J" => "VBP", #atb3
				"IV3FD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBP",
				"IV3FD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:SJ" => "VBP",
				"IV3FD+VERB_IMPERFECT+IVSUFF_SUBJ:3D" => "VBP", #new buckv1.0
				"IV3FP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:FP" => "VBP",
				"IV3FP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:3FP" => "VBP",
				"IV3FS\+VERB\_IMPERFECT" => "VBP",
				"IV3MD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBP",
				"IV3MD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:SJ" => "VBP",
				"IV3MD+VERB_IMPERFECT+IVSUFF_SUBJ:3D" => "VBP", #buckv1.0 over atb3
				"IV3MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBP",
				"IV3MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:SJ" => "VBP",
				"IV3MP+VERB_IMPERFECT+IVSUFF_SUBJ:3MP_MOOD:SJ" => "VBP",	#new
				"IV3MD\+VERB\_IMPERFECT" => "VBP",		#NEWCOLLAPSE
				"IV3MP\+VERB\_IMPERFECT" => "VBP",		#NEWCOLLAPSE
				"IV3MS\+VERB\_IMPERFECT" => "VBP",				
				"FUT\+IV3FS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"FUT\+IV3MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"IV3FS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"IV3FS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"IV3FS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:J" => "VBP",
				"IV3MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:I" => "VBP",
				"IV3MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"IV3MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:J" => "VBP",
				"SUBJUNC\+IV1P\+VERB\_IMPERFECT" => "VBP",
				"SUBJUNC\+IV1P\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"SUBJUNC\+IV1S\+VERB\_IMPERFECT" => "VBP",
				"SUBJUNC\+IV1S\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"SUBJUNC+IV2MS+VERB_IMPERFECT" => "VBP",
				"SUBJUNC+IV2FS+VERB_IMPERFECT" => "VBP",
				"SUBJUNC+IV2FS+VERB_IMPERFECT+IVSUFF_SUBJ:2FS_MOOD:SJ" => "VBP",
				"SUBJUNC+IV2FP+VERB_IMPERFECT+IVSUFF_SUBJ:FP" => "VBP",
				"SUBJUNC\+IV3MS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"SUBJUNC\+IV3MS\+VERB\_IMPERFECT" => "VBP",
				"SUBJUNC\+IV3MD\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:D\_MOOD\:SJ" => "VBP",
				"SUBJUNC\+IV3MP\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:MP\_MOOD\:SJ" => "VBP",
				"SUBJUNC\+IV3FS\+VERB\_IMPERFECT\+IVSUFF\_MOOD\:S" => "VBP",
				"SUBJUNC\+IV3FS\+VERB\_IMPERFECT" => "VBP",
				"SUBJUNC+IV3FP+VERB_IMPERFECT+IVSUFF_SUBJ:FP" => "VBP",
				"NEG\_PART\+PVSUFF\_SUBJ\:3FS" => "VBP",
				"NEG\_PART\+PVSUFF\_SUBJ\:1P" => "VBP",
				"NEG\_PART\+PVSUFF\_SUBJ\:3MS" => "VBP",
				"NEG\_PART\+PVSUFF\_SUBJ\:3MP" => "VBP",
				"NEG\_PART\+PVSUFF\_SUBJ\:1S" => "VBP",	#new
				"NEG_PART+PVSUFF_SUBJ:2MS" => "VBP",	#new
				"NEG_PART+PVSUFF_SUBJ:2FS" => "VBP",	#new
				"NEG_PART+PVSUFF_SUBJ:3FP" => "VBP",	#new
				"FUT\+IV3FS\+VERB\_PASSIVE" => "VBN",
				"FUT\+IV3MS\+VERB\_PASSIVE" => "VBN",
				"IV1P\+VERB\_PASSIVE" => "VBN",
				"IV1S\+VERB\_PASSIVE" => "VBN",
				"IV2MS\+VERB\_PASSIVE" => "VBN",
				"IV3FS\+VERB\_PASSIVE" => "VBN",
				"IV3MP\+VERB\_PASSIVE\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBN",
				"IV3MS\+VERB\_PASSIVE" => "VBN",
				"VERB\_PASSIVE" => "VBN",
				"VERB\_PASSIVE\+PVSUFF\_SUBJ\:1S" => "VBN",
				"VERB\_PASSIVE\+PVSUFF\_SUBJ\:3FS" => "VBN",
				"VERB\_PASSIVE\+PVSUFF\_SUBJ\:3MD" => "VBN",
				"VERB\_PASSIVE\+PVSUFF\_SUBJ\:3MP" => "VBN",
				"VERB\_PASSIVE\+PVSUFF\_SUBJ\:3MS" => "VBN",
				"FUT\+IV2MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"FUT\+IV3FS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"FUT\+IV3FS\+VERB\_IMPERFECT\_PASSIVE" => "VBN",
				"FUT\+IV3MD\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_SUBJ\:D\_MOOD\:I" => "VBN",
				"FUT\+IV3MP\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBN",
				"FUT\+IV3MS\+VERB\_IMPERFECT\_PASSIVE" => "VBN",
				"FUT\+IV3MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"FUT+IV3MS+VERB\_IMPERFECT\_PASSIVE+IVSUFF_MOOD:S" => "VBN", #atb3
				"IV3FS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"IV3MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"IV1P\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"IV1P\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"IV1S\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"IV1S\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"IV2MS\+VERB\_IMPERFECT\_PASSIVE" => "VBN",
				"IV2MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:I" => "VBN",
				"IV2MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"IV2MS+VERB\_IMPERFECT\_PASSIVE+IVSUFF_MOOD:J" => "VBN", #atb3
				"IV3FS\+VERB\_IMPERFECT\_PASSIVE" => "VBN",
				"IV3FS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"IV3FS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:J" => "VBN",
				"IV3MP\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_SUBJ\:MP\_MOOD\:I" => "VBN",
				"IV3MP\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_SUBJ\:MP\_MOOD\:SJ" => "VBN",
				"IV3MS\+VERB\_IMPERFECT\_PASSIVE" => "VBN",
				"IV3MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"IV3MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:J" => "VBN",
				"IV3MD\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF_SUBJ:D_MOOD:SJ" => "VBN",
				"IV3MD\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF_SUBJ:D_MOOD:J" => "VBN",
				"IV3MD\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF_SUBJ:D_MOOD:S" => "VBN",
				"IV3MD\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF_SUBJ:D_MOOD:I" => "VBN",
				"VERB\_PERFECT\_PASSIVE+PVSUFF_SUBJ:1P" => "VBN", #atb3
				"VERB\_PERFECT\_PASSIVE+PVSUFF_SUBJ:1S" => "VBN", #atb3
				"VERB\_PERFECT\_PASSIVE\+PVSUFF\_SUBJ\:3FS" => "VBN",
				"VERB\_PERFECT\_PASSIVE\+PVSUFF\_SUBJ\:3FD" => "VBN",
				"VERB\_PERFECT\_PASSIVE\+PVSUFF\_SUBJ\:3FP" => "VBN",
				"VERB\_PERFECT\_PASSIVE\+PVSUFF\_SUBJ\:3MD" => "VBN",
				"VERB\_PERFECT\_PASSIVE\+PVSUFF\_SUBJ\:3MP" => "VBN",
				"VERB\_PERFECT\_PASSIVE\+PVSUFF\_SUBJ\:3MS" => "VBN",
				"SUBJUNC\+IV3MS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"SUBJUNC\+IV3FS\+VERB\_IMPERFECT\_PASSIVE\+IVSUFF\_MOOD\:S" => "VBN",
				"INTERJ" => "UH",
				"DET+INTERJ" => "UH",
				"DET+INTERJ+CASE_DEF_NOM" => "UH", #atb3
				"INTERJ\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "UH",
				"INTERJ\+CASE\_INDEF\_NOM" => "UH",
				"INTERJ\+CASE\_INDEF\_ACC" => "UH",
				"INTERJ\+CASE\_INDEF\_GEN" => "UH",
				"CVSUFF\_DO\:3MS" => "PRP",
				"CVSUFF_DO:3MP" => "PRP",
				"CVSUFF_DO:3FP" => "PRP",
				"CVSUFF_DO:3FS" => "PRP",
				"CVSUFF_DO:1P" => "PRP", #new buckv1.0
				"IVSUFF\_DO\:1P" => "PRP",
				"IVSUFF\_DO\:1S" => "PRP",
				"IVSUFF\_DO\:2MP" => "PRP",
				"IVSUFF\_DO\:2MS" => "PRP",
				"IVSUFF\_DO\:3D" => "PRP",
				"IVSUFF\_DO\:3FS" => "PRP",
				"IVSUFF\_DO\:3MP" => "PRP",
				"IVSUFF\_DO\:3MS" => "PRP",
				"IVSUFF\_DO\:2FP" => "PRP",
				"IVSUFF\_DO\:2FS" => "PRP",		#NEWCOLLAPSE
				"IVSUFF\_DO\:3FP" => "PRP",		#new
				"IVSUFF_DO:2D" => "PRP",	#new
				"PRON" => "PRP",
				"PRON\_1P" => "PRP",
				"PRON\_1S" => "PRP",
				"PRON\_2FS" => "PRP",
				"PRON\_2MP" => "PRP",
				"PRON\_2MS" => "PRP",
				"PRON\_2D" => "PRP", #atb3
				"PRON\_3D" => "PRP",
				"PRON\_3FP" => "PRP",
				"PRON\_3FS" => "PRP",
				"PRON\_3MP" => "PRP",
				"PRON\_3MS" => "PRP",
				"PRON\_2FP" => "PRP",	#new
				"PVSUFF\_DO\:1P" => "PRP",
				"PVSUFF\_DO\:1S" => "PRP",
				"PVSUFF\_DO\:2MS" => "PRP",
				"PVSUFF\_DO\:3D" => "PRP",
				"PVSUFF\_DO\:3FS" => "PRP",
				"PVSUFF\_DO\:3MP" => "PRP",
				"PVSUFF\_DO\:3MS" => "PRP",
				"PVSUFF\_SUBJ\:1P" => "PRP",
				"PVSUFF\_SUBJ\:1S" => "PRP",
				"PVSUFF\_SUBJ\:3FS" => "PRP",
				"PVSUFF\_DO\:2FS" => "PRP",		#NEWCOLLAPSE
				"PVSUFF\_DO\:2FP" => "PRP",	#new
				"PVSUFF_DO:2D" => "PRP",	#new
				"PVSUFF\_DO\:3FP" => "PRP",	#new
				"PVSUFF\_DO\:2MP" => "PRP",	#new
				"PVSUFF_SUBJ:2MS" => "PRP",	#new
				"PVSUFF_SUBJ:2FS" => "PRP",	#new
				"POSS\_PRON\_1P" => "PRPS",	#changed from PRP$ for roy
				"POSS\_PRON\_1S" => "PRPS",
				"POSS\_PRON\_2FS" => "PRPS",
				"POSS\_PRON\_2MP" => "PRPS",
				"POSS\_PRON\_2MS" => "PRPS",
				"POSS\_PRON\_2D" => "PRPS", #buckv1.0 over atb3
				"POSS\_PRON\_3D" => "PRPS",
				"POSS\_PRON\_3FP" => "PRPS",
				"POSS\_PRON\_3FS" => "PRPS",
				"POSS\_PRON\_3MP" => "PRPS",
				"POSS\_PRON\_3MS" => "PRPS",
				"POSS\_PRON\_2FP" => "PRPS",	 #new
				"REL\_ADV" => "CC",	#change from WRB to CC for atb1,2,3
				"REL\_PRON" => "WP",
				"REL\_PRON+CASE_INDEF_ACC" => "WP",
				"REL\_PRON\+PREP" => "WP",
				"REL\_PRON\+NSUFF\_MASC\_SG\_ACC\_INDEF" => "WP",
				"VERB\_PERFECT" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:1P" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:1S" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:2FS" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:2MP" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:2MS" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3FD" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3FP" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3FS" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3FD" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3MD" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3MP" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:3MS" => "VBD",
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:2FP" => "VBD",	#new
				"VERB\_PERFECT\+PVSUFF\_SUBJ\:2D" => "VBD",	#new
				"VERB_PERFECT+PVSUFF_SUBJ:3MS+PVSUFF_SUBJ:3FS" => "VBD", #atb3, error?
				"VERB_PERFECT+PVSUFF_SUBJ:3MS+PVSUFF_SUBJ:3MS" => "VBD", #atb3
				"NEG\_PART\+VERB\_PERFECT\+PVSUFF\_SUBJ\:3FS" => "VBD",
				"NEG\_PART\+VERB\_PERFECT\+PVSUFF\_SUBJ\:3MS" => "VBD",
				"VERB\_IMPERATIVE\+CVSUFF\_SUBJ\:2MP" => "VBI",
				"VERB\_IMPERATIVE\+CVSUFF\_SUBJ\:2MS" => "VBI",
				"VERB_IMPERATIVE+CVSUFF_SUBJ:2FS" => "VBI",
				#"IV2FS\+VERB\_IMPERFECT\+IVSUFF\_SUBJ\:2FS\_MOOD\:I" => "VBP",
				"NUM" => "CD",
				"NUM+NSUFF_FEM_SG" => "CD",
				"NUM+NSUFF_FEM_PL" => "CD",
				"NUM\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "CD",	#added atb3
				"NUM\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "CD",	#added atb3
				"NUM\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "CD",	#added atb3
				"NUM\+NSUFF\_FEM\_SG\+CASE_INDEF_ACC" => "CD",
				"NUM\+NSUFF\_FEM\_SG\+CASE_INDEF_NOM" => "CD",
				"NUM\+NSUFF\_FEM\_SG\+CASE_INDEF_GEN" => "CD",
				"NUM\+NSUFF\_FEM\_PL\+CASE\_DEF\_GEN" => "CD",	#added atb3
				"NUM\+NSUFF\_FEM\_PL\+CASE\_DEF\_NOM" => "CD",	#added atb3
				"NUM\+NSUFF\_FEM\_PL\+CASE\_DEF\_ACC" => "CD",	#added atb3
				"NUM+CASE_DEF_ACC" => "CD",
				"NUM+CASE_DEF_GEN" => "CD",
				"NUM+CASE_DEF_NOM" => "CD",
				"NUM+CASE_INDEF_GEN" => "CD",
				"NUM+CASE_INDEF_NOM" => "CD",
				"NUM+CASE_INDEF_ACC" => "CD",
				"NUM+NSUFF_MASC_DU_GEN" => "CD",
				"NUM+NSUFF_MASC_DU_ACC" => "CD",
				"NUM+NSUFF_MASC_DU_NOM" => "CD",
				"NUM+NSUFF_MASC_DU_ACC_POSS" => "CD",
				"NUM+NSUFF_MASC_DU_GEN_POSS" => "CD",
				"NUM+NSUFF_MASC_DU_ACC_POSS" => "CD",
				"NUM+NSUFF_MASC_PL_GEN" => "CD",
				"NUM+NSUFF_MASC_PL_ACC" => "CD",
				"NUM+NSUFF_MASC_PL_NOM" => "CD",
				"NUM+NSUFF_MASC_PL_GEN_POSS" => "CD",
				"NUM+NSUFF_MASC_PL_ACC_POSS" => "CD",
				"NUM+NSUFF_MASC_PL_NOM_POSS" => "CD",
				"NUM+NSUFF_FEM_DU_GEN" => "CD",
				"NUM+NSUFF_FEM_DU_ACC" => "CD",
				"NUM+NSUFF_FEM_DU_NOM" => "CD",
				"NUM+NSUFF_FEM_DU_GEN_POSS" => "CD",
				"NUM+NSUFF_FEM_DU_ACC_POSS" => "CD",
				"NUM+NSUFF_FEM_DU_NOM_POSS" => "CD",
				"NUM" => "CD",
				"DET+NUM" => "CD",
				"DET+NUM+NSUFF_FEM_SG" => "CD",
				"DET\+NUM\+NSUFF\_FEM\_SG\+CASE\_DEF\_GEN" => "CD",	#added atb3
				"DET\+NUM\+NSUFF\_FEM\_SG\+CASE\_DEF\_NOM" => "CD",	#added atb3
				"DET\+NUM\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "CD",	#added atb3
				"DET\+NUM\+NSUFF\_FEM\_SG\+CASE_INDEF_ACC" => "CD",
				"DET\+NUM\+NSUFF\_FEM\_SG\+CASE_INDEF_NOM" => "CD",
				"DET\+NUM\+NSUFF\_FEM\_SG\+CASE_INDEF_GEN" => "CD",
				"DET\+NUM+CASE_DEF_ACC" => "CD",
				"DET\+NUM+CASE_DEF_GEN" => "CD",
				"DET\+NUM+CASE_DEF_NOM" => "CD",
				"DET\+NUM+CASE_INDEF_GEN" => "CD",
				"DET\+NUM+CASE_INDEF_NOM" => "CD",
				"DET\+NUM+CASE_INDEF_ACC" => "CD",
				"DET\+NUM+NSUFF_MASC_DU_GEN_POSS" => "CD",
				"DET\+NUM+NSUFF_MASC_PL_GEN" => "CD",
				"DET\+NUM+NSUFF_MASC_PL_ACC" => "CD",
				"PUNC" => "PUNC",	#added
				"NUMERIC_COMMA" => "NUMERIC_COMMA",	#added
				#added for dp2v2, the test trees were collapsed, and missing collapsed were added
				"NOUN\+NSUFF\_FEM\_SG\+CASE\_DEF\_ACC" => "NN",
				"VERB\_PASSIVE\+CVSUFF\_SUBJ\:2FS" => "VBN",
				"NOUN\+CASE_DEF_GEN\+POSS_PRON_3FS" => "NN"
);


1;
