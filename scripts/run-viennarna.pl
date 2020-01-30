#!/usr/bin/perl -w
#run-viennarna.pl

use strict;
use Class::Struct;
use lib '/groups/eddy/home/rivase/src/tornado/scripts';
use lib '/Users/rivase/src/tornado/scripts';
use FUNCS;

use vars qw ($opt_d $opt_f $opt_C $opt_g $opt_G $opt_M $opt_U $opt_S $opt_t $opt_V $opt_v);  # required if strict used
use Getopt::Std;
getopts ('Cd:fg:G:M:S:t:UV:v');

# Print a helpful message if the user provides no input file.
if (!@ARGV) {
        print "usage:  run-viennarna.pl [options] infile outfile\n\n";
        print "options:\n";
	print "-d        :  dangles [0|1|2] [with -p  it is -d2]\n";
	print "-f        :  infile in fasta format [default is stockholm format]\n";
	print "-g <x>    :  smallest value of log2(gamma) [default gamma=2^{-5}]\n";
	print "-G <x>    :  largest value of log2(gamma) [default gamma=2^{10}]\n";
	print "-M <gamma>:  MEA [default is cyk]\n";
	print "-C        :  centroid [default is cyk]\n";
	print "-S <x>    :  gamma step value [default 0.5]\n";
	print "-t <f>    :  write input sequences in sto format to <f>\n";
	print "-U        :  AUC [default is cyk]\n";
	print "-V        :  version [default 1.8.4]\n";
	print "-v        :  be verbose\n";
	exit;
}
my $infile  = shift;
my $outfile = shift;

my $toutfile = "";
if ($opt_t)  { $toutfile = "$opt_t"; system("rm $toutfile\n"); }

my $auc = 0;
if ($opt_U) { $auc = 1; }

my $gamma_min = exp(-5.0*log(2.0));
if ($opt_g) { $gamma_min = exp($opt_g*log(2.0)); }

my $gamma_max = exp(10.0*log(2.0));
if ($opt_G) { $gamma_max = exp($opt_G*log(2.0)); }

my $gamma_step = 0.5;
if ($opt_S) { $gamma_step = $opt_S; }

my $gamma = -1;
if ($opt_M) { $gamma = $opt_M; }
if ($opt_U) { $gamma = $gamma_min; }

my $verbose = 0;
if ($opt_v) { $verbose = 1;}

my $version = "ViennaRNA-1.8.4";
if ($opt_V) { $version = "$opt_V"; }

my $viennarna = "~/alien-src/RNA/ViennaRNA/$version/Progs/RNAfold";

if ($verbose) {
    print "infile: $infile\n";
    print "outfile: $outfile\n";
}
 
#make local copy of input file to avoid overriding
my $local_infile = "$outfile.input";
system("cp $infile $local_infile\n");

run_viennarna($local_infile, $outfile, $toutfile, $gamma, $gamma_max, $gamma_step);
system("rm $local_infile\n");

#######################################
sub run_viennarna {
    my ($infile, $outfile, $toutfile, $gamma, $gamma_max, $gamma_step) = @_;
    
    my $fastafile = "$infile.fa";
    my $vr_outfile = "$outfile.out";

    my $new_sq_name;
    my $sq_name;
    my $sq;

    #convert to fasta if necesary
    if ($opt_f) { system("cp $infile $fastafile\n"); }
    else        { FUNCS::stk2fasta($infile, $fastafile, $verbose); }

    system("rm $outfile\n");
    system("rm $vr_outfile\n");
    my $nsq = 0;
    my $ntsq = 0;
    open(FASTAFILE, "$fastafile");
    while(<FASTAFILE>) {
	if (/^\>(.+)/) { 
	    $new_sq_name = $1; 
	    run_viennarna_forreal($nsq, \$ntsq, $sq_name, $sq, $infile, $fastafile, $vr_outfile, $toutfile, $gamma, $gamma_max, $gamma_step);

	    $nsq ++;
	    $sq_name = $new_sq_name; 
	    $sq = "";
	}
	elsif (/^(\S+)/) { 
	    $sq .= "$_"; $sq =~ s/\n//g;
	}
    }
    close (FASTAFILE);
    run_viennarna_forreal($nsq, \$ntsq, $sq_name, $sq, $infile, $fastafile, $vr_outfile, $toutfile, $gamma, $gamma_max, $gamma_step);
    if ($verbose) { system("more $vr_outfile\n"); }
    
    viennarna2stk($vr_outfile, $outfile);
    if ($verbose) { system("more $outfile\n"); }

    system("rm $fastafile\n");
    system("rm $vr_outfile\n");
}
       
sub run_viennarna_forreal {
    my ($nsq, $ret_ntsq, $sq_name, $sq, $infile, $fastafile, $outfile, $toutfile, $gamma, $gamma_max, $gamma_step) = @_;
    
    my $onefile;
    my $auc_gamma = $gamma;

    my $sq_given_ss;

    if ($nsq > 0) {
        # remove ambiguity
	FUNCS::seq_remove_ambiguity(\$sq);
	FUNCS::seq_remove_Ns(\$sq);

	$onefile = "$fastafile.n$nsq";
	open(FILE, ">$onefile");
	printf FILE ">$sq_name\n$sq\n";
	close (FILE);

	#get sq_given_ss
	my $sqlen = length($sq);
	if (!$opt_f && $toutfile) { $sq_given_ss = FUNCS::extract_ss_from_stofile($sq_name, $sqlen, $infile, $verbose); }
	if (length($sq_given_ss) != $sqlen) { print "name=$sq_name: seq and ss don't have the same legnth\n$sq\n$sq_given_ss\n"; die; }

	if ($verbose) { print "onefasta: $onefile\n"; system("more $onefile\n"); }
	
	if ($auc == 0) {
	    $$ret_ntsq ++;
	    run_viennarna_forreal_onetime($$ret_ntsq, $onefile, $gamma, $outfile, $sq_name, $sq, $sq_given_ss, $toutfile);
	}
	else {
	    while ($auc_gamma <= $gamma_max) {
		$$ret_ntsq ++;
		run_viennarna_forreal_onetime($$ret_ntsq, $onefile, $auc_gamma, $outfile, $sq_name, $sq, $sq_given_ss, $toutfile);
		$auc_gamma *= exp(log(2.0)*$gamma_step);
	    }
	}
	
	system("rm $onefile\n");
	system("rm *.ps\n");
    }
}

sub run_viennarna_forreal_onetime {

    my ($nsq, $onesqfile, $gamma, $outfile, $sq_name, $sq, $sq_given_ss, $toutfile) = @_;

    my $cmd = "$viennarna "; 
    if ($auc)   { $cmd .= "-p -MEA $gamma "; }
    if ($opt_M) { $cmd .= "-p -MEA $gamma "; }
    if ($opt_C) { $cmd .= "-p -MEA ";  }
    if ($opt_d) { $cmd .= "-d$opt_d "; }
    $cmd .= "-noPS <$onesqfile "; # -noPS do not produce postcript dwaing of mfe structure
    
    if ($version =~/^ViennaRNA-1.4$/) { $cmd = "$viennarna < $onesqfile "; }
    if ($verbose) { system("echo $cmd\n"); }
    system("$cmd >> $outfile\n");

    # add sq with sq_ss to toutfile
    if (!$opt_f && $toutfile) {
	FUNCS::stk_oneseq($toutfile, $nsq, $sq_name, $sq, $sq_given_ss, $verbose);
    }
}

sub viennarna2stk {
    my ($vr_outfile, $outfile) = @_;
    
    if ($verbose) { system("more $vr_outfile\n"); }

    my $short_name;
    my $new_sq_name;
    my $sq_name;
    my $sq;
    my $ss;

    my $nsq = 0;
    my $targetnl;
    my $nl;
    if    ($opt_M) { $targetnl = 4; } # mea gamma
    elsif ($opt_U) { $targetnl = 4; } # mea gamma
    elsif ($opt_C) { $targetnl = 3; } # centroid
    else           { $targetnl = 1; } # cyk
    open(OUTFILE, "$vr_outfile");
    while(<OUTFILE>) {
	if (/^\>(.+)/) { 
	    $new_sq_name = $1; 

	    if ($nsq > 0) { FUNCS::stk_oneseq($outfile, $nsq, $sq_name, $sq, $ss, $verbose); }

	    $nsq ++;
	    $sq_name = $new_sq_name; 
	    $sq = "";
	    $ss = "";
	    $nl = 0;
	}
	elsif ($nl == 0 && /^([^\.\(\)\s]+)/) { #first line is the sequence
	    $sq = "$1"; 
	    $nl ++;
	}
	elsif (($nl == $targetnl) && /^([\.\(\)]+)/) { 
	    $ss = "$1"; # each structure appears as a line. Pick fist for mfe,  3th for centroid, and 4th for mea
	    $nl ++;
	}
	elsif (/^(\S+)/) { 
	    $nl ++;
	}

    }
    close (OUTFILE);
    FUNCS::stk_oneseq($outfile, $nsq, $sq_name, $sq, $ss, $verbose);
}

