#!/usr/bin/perl -w
#Simfold_sh.pl

use strict;
use Class::Struct;

use vars qw ($opt_v);  # required if strict used
use Getopt::Std;
getopts ('v');

# Print a helpful message if the user provides no input file.
if (@ARGV) {
        print "usage:  Simfold_sh.pl [options] \n\n";
        print "options:\n";
	print "-v        :  be verbose\n";
	exit;
}

my $verbose = 0; if ($opt_v) { $verbose = 1; }

#MAIN DIRECTORY
my $tornado_full = "/groups/eddy/home/rivase/src/tornado";
my $dir_full     = "$tornado_full/notebook/milestone8/simfold/MultiRNAFold-2.0";

my $tornado      = "~/src/tornado";
my $notebook     = "$tornado/notebook/milestone8";
my $dir          = "$notebook/simfold/MultiRNAFold-2.0";
system("mkdir $dir\n");

#fixed in this case
my $Gname    = "MultiRNAFold-2.0";
my $foldtype = "cyk";

#SCRIPTS
my $scripts        = "$tornado_full/scripts";
my $simfold_script = "$scripts/run-simfold.pl";
my $process_script = "$scripts/process_tornado_fold.pl";

#SHSCRIPTS
my $shscripts = "$tornado_full/shscripts";
my $my_shscripts = "$shscripts/$Gname";
system("rm -rf $my_shscripts\n");
system("mkdir $my_shscripts\n");
my $head = "m8";
my $qsub_cmd = "-cwd -b y -V -j y ";

my $NP = 8;
my @param;
$param[0] = "turner_parameters_fm363_constrdangles";
$param[1] = "CG_best_parameters_ISMB2007";
$param[2] = "BLFRstar";
$param[3] = "BLstar";
$param[4] = "BLnodangles";
$param[5] = "NOMCG";
$param[6] = "CGstar";
$param[7] = "CG1.1";

my $simfolddir       = "~/alien-src/RNA/SimFold";
my $simfolddir_ver   = "$simfolddir/$Gname";
my $RNA2010_paramdir = "$simfolddir/RNA2010";
my @paramfile;
$paramfile[0] = "$simfolddir_ver/params/$param[0].txt";
$paramfile[1] = "$simfolddir_ver/params/$param[1].txt";
$paramfile[2] = "$RNA2010_paramdir/data/parameters_$param[2].txt";
$paramfile[3] = "$RNA2010_paramdir/data/parameters_$param[3].txt";
$paramfile[4] = "$RNA2010_paramdir/data/parameters_$param[4].txt";
$paramfile[5] = "$RNA2010_paramdir/data/parameters_$param[5].txt";
$paramfile[6] = "$RNA2010_paramdir/data/parameters_$param[6].txt";
$paramfile[7] = "$RNA2010_paramdir/data/parameters_$param[7].txt";

#TESTS SETS 
my $datadir = "$tornado_full/data/TORNADO/sto";
my $N = 10;
my @RNA;
$RNA[0]  = "tRNA";
$RNA[1]  = "srp";
$RNA[2]  = "tmRNA";
$RNA[3]  = "RNaseP";
$RNA[4]  = "5s";
$RNA[5]  = "telomerase";
$RNA[6]  = "grp1";
$RNA[7]  = "grp2w";
$RNA[8]  = "S-Processed-TES";
$RNA[9]  = "S-Full-Test";

my @trustedRNA;
$trustedRNA[0]  = "$datadir/TORNADO_Test_$RNA[0]_no-Tr1Tr2Tr3.sto";
$trustedRNA[1]  = "$datadir/TORNADO_Test_$RNA[1]_no-Tr1Tr2Tr3.sto";
$trustedRNA[2]  = "$datadir/TORNADO_Test_$RNA[2]_no-Tr1Tr2Tr3.sto";
$trustedRNA[3]  = "$datadir/TORNADO_Test_$RNA[3]_no-Tr1Tr2Tr3.sto";
$trustedRNA[4]  = "$datadir/TORNADO_Test_$RNA[4]_no-Tr1Tr2Tr3.sto";
$trustedRNA[5]  = "$datadir/TORNADO_Test_$RNA[5]_no-Tr1Tr2Tr3.sto";
$trustedRNA[6]  = "$datadir/TORNADO_Test_$RNA[6]_no-Tr1Tr2Tr3.sto";
$trustedRNA[7]  = "$datadir/TORNADO_Test_$RNA[7]_no-Tr1Tr2Tr3.sto";
$trustedRNA[8]  = "$datadir/TORNADO_Test_$RNA[8]_no-Tr1Tr2Tr3.sto";
$trustedRNA[9]  = "$datadir/TORNADO_Test_$RNA[9]_no-Tr1Tr2Tr3.sto";

my $N_Rfam3D = 1;
my @Rfam3D;
$Rfam3D[0]  = "Rfam3D";
my @trustedRfam3D;
for (my $n = 0; $n < $N_Rfam3D; $n ++) {
    $trustedRfam3D[$n]  = "$datadir/TORNADO_Test_$Rfam3D[$n]_no-Tr1Tr2Tr3.sto";
}

my $Nboostrap = 10;
my @boostrap;
for (my $n = 0; $n < $Nboostrap; $n ++) {
    $boostrap[$n]  = "TORNADO_Test_no-Tr1Tr2Tr3-boostrap$n";
}
my @trustedboostrap;
for (my $n = 0; $n < $Nboostrap; $n ++) {
    $trustedboostrap[$n]  = "$datadir/$boostrap[$n].sto";
}
my @np_trustedboostrap;
for (my $n = 0; $n < $Nboostrap; $n ++) {
    $np_trustedboostrap[$n] = 20;
}
my @boostrapRfam3D;
for (my $n = 0; $n < $Nboostrap; $n ++) {
    $boostrapRfam3D[$n]  = "TORNADO_Test_Rfam3D_no-Tr1Tr2Tr3-boostrap$n";
}
my @trustedboostrapRfam3D;
for (my $n = 0; $n < $Nboostrap; $n ++) {
    $trustedboostrapRfam3D[$n]  = "$datadir/$boostrapRfam3D[$n].sto";
}
my @np_trustedboostrapRfam3D;
for (my $n = 0; $n < $Nboostrap; $n ++) {
    $np_trustedboostrapRfam3D[$n] = 10;
}

my @trustedjacknife1RNA;
$trustedjacknife1RNA[0]  = $trustedRNA[0];
$trustedjacknife1RNA[1]  = $trustedRNA[1];
$trustedjacknife1RNA[2]  = $trustedRNA[2];
$trustedjacknife1RNA[3]  = $trustedRNA[3];
$trustedjacknife1RNA[4]  = $trustedRNA[4];
$trustedjacknife1RNA[5]  = $trustedRNA[5];
$trustedjacknife1RNA[6]  = $trustedRNA[6];
$trustedjacknife1RNA[7]  = $trustedRNA[7];
$trustedjacknife1RNA[8]  = $trustedRNA[8];
$trustedjacknife1RNA[9]  = $trustedRNA[9];

my @trustedjacknife2RNA;
$trustedjacknife2RNA[0]  = $trustedRNA[0];
$trustedjacknife2RNA[1]  = $trustedRNA[1];
$trustedjacknife2RNA[2]  = $trustedRNA[2];
$trustedjacknife2RNA[3]  = $trustedRNA[3];
$trustedjacknife2RNA[4]  = $trustedRNA[4];
$trustedjacknife2RNA[5]  = $trustedRNA[5];
$trustedjacknife2RNA[6]  = $trustedRNA[6];
$trustedjacknife2RNA[7]  = $trustedRNA[7];
$trustedjacknife2RNA[8]  = $trustedRNA[8];
$trustedjacknife2RNA[9]  = $trustedRNA[9];

my @trustedjacknife3RNA;
$trustedjacknife3RNA[0]  = "$datadir/TORNADO_Test_$RNA[0].sto";
$trustedjacknife3RNA[1]  = "$datadir/TORNADO_Test_$RNA[1].sto";
$trustedjacknife3RNA[2]  = "$datadir/TORNADO_Test_$RNA[2].sto";
$trustedjacknife3RNA[3]  = "$datadir/TORNADO_Test_$RNA[3].sto";
$trustedjacknife3RNA[4]  = "$datadir/TORNADO_Test_$RNA[4].sto";
$trustedjacknife3RNA[5]  = "$datadir/TORNADO_Test_$RNA[5].sto";
$trustedjacknife3RNA[6]  = "$datadir/TORNADO_Test_$RNA[6].sto";
$trustedjacknife3RNA[7]  = "$datadir/TORNADO_Test_$RNA[7].sto";
$trustedjacknife3RNA[8]  = "$datadir/TORNADO_Test_$RNA[8].sto";
$trustedjacknife3RNA[9]  = "$datadir/TORNADO_Test_$RNA[9].sto";

create_parent_readme_file($dir_full);

for (my $p = 0; $p < $NP; $p ++) { 
    my $dir = "$dir_full/$param[$p]";
    system("mkdir $dir\n"); 
    create_readme_file($param[$p], $paramfile[$p], $dir);
}


##########################################################################
sub create_parent_readme_file {
    my ($dir) = @_;
    
    my $readme_file = "$dir/00README";
    system("rm $readme_file\n");
    open(FILE, ">$readme_file");	
    
    for (my $p = 0; $p < $NP; $p ++) { 
	my $shfile = "$my_shscripts/m8_fold_cyk_simfold_$param[$p].sh";
	print FILE "sh $shfile\n";
    }
    print FILE "\n";
    
   for (my $p = 0; $p < $NP; $p ++) { 
	my $shfile = "$my_shscripts/m8_fold_Rfam3D_cyk_simfold_$param[$p].sh";
	print FILE "sh $shfile\n";
    }
    print FILE "\n";
    
    #boostrap
    for (my $p = 0; $p < $NP; $p ++) { 
	my $shfile = "$my_shscripts/m8_fold_boostrap_cyk_simfold_$param[$p].sh";
	print FILE "sh $shfile\n";
    }
    print FILE "\n";

   for (my $p = 0; $p < $NP; $p ++) { 
	my $shfile = "$my_shscripts/m8_fold_Rfam3D_boostrap_cyk_simfold_$param[$p].sh";
	print FILE "sh $shfile\n";
    }
    print FILE "\n";
 
   #jacknife
    for (my $j = 1; $j <= 3; $j ++) {
	for (my $p = 0; $p < $NP; $p ++) { 
	    my $shfile = "$my_shscripts/m8_fold_jacknife$j\_cyk_simfold_$param[$p].sh";
	    print FILE "sh $shfile\n";
	}
	print FILE "\n";
    }
    
    for (my $p = 0; $p < $NP; $p ++) { 
	my $process_cmd = "";;
	$process_cmd .= "-s "; # scores
	$process_cmd .= "-T "; # no mpi
	$process_cmd .= "$dir/$param[$p]";
	print FILE "$process_script $process_cmd\n";
    }
    
    for (my $p = 0; $p < $NP; $p ++) { 
	my $process_cmd = "";;
	$process_cmd .= "-s "; # scores
	$process_cmd .= "-T "; # no mpi
	$process_cmd .= "-a "; # Rfam3D
	$process_cmd .= "$dir/$param[$p]";
	print FILE "$process_script $process_cmd\n";
    }
    
    #boostrap
    for (my $p = 0; $p < $NP; $p ++) { 
	my $process_cmd = "";;
	$process_cmd .= "-s "; # scores
	$process_cmd .= "-T "; # no mpi
	$process_cmd .= "-b "; # boostrap
	$process_cmd .= "$dir/$param[$p]";
	print FILE "$process_script $process_cmd\n";
    }
    
    for (my $p = 0; $p < $NP; $p ++) { 
	my $process_cmd = "";;
	$process_cmd .= "-s "; # scores
	$process_cmd .= "-T "; # no mpi
	$process_cmd .= "-a "; # Rfam3D
	$process_cmd .= "-b "; # boostrap
	$process_cmd .= "$dir/$param[$p]";
	print FILE "$process_script $process_cmd\n";
    }
    
    for (my $j = 1; $j <= 3; $j ++) {
	for (my $p = 0; $p < $NP; $p ++) { 
	    my $process_cmd = "";;
	    $process_cmd .= "-j $j "; # jacknife
	    $process_cmd .= "-s ";    # scores
	    $process_cmd .= "-T ";    # no mpi
	    $process_cmd .= "$dir/$param[$p]";
	    print FILE "$process_script $process_cmd\n";
	}
    }
    close(FILE);
}

sub create_readme_file {
    my ($param, $paramfile, $dir) = @_;
    
    my $readme_file = "$dir/00README";
      system("rm $dir/00READNE\n"); 
  
    open(FILE, ">$readme_file");	
    if ($verbose) { print "cd $dir\n\n"; }
    print FILE "cd $dir\n\n";
 
    my $shfile;
    my $process_cmd;

    $shfile = "$my_shscripts/m8_fold_cyk_simfold_$param.sh";
    print FILE "sh $shfile\n";
    $process_cmd = "";
    $process_cmd .= "-s "; # scores
    $process_cmd .= "-T "; # no mpi
    $process_cmd .= "$dir";
    print FILE "$process_script $process_cmd\n\n";
    create_sh_file($N,            \@RNA,         $param, $paramfile, $dir, $shfile, \@trustedRNA,            0);

    $shfile = "$my_shscripts/m8_fold_Rfam3D_cyk_simfold_$param.sh";
    print FILE "sh $shfile\n";
    $process_cmd = "";
    $process_cmd .= "-s "; # scores
    $process_cmd .= "-T "; # no mpi
    $process_cmd .= "-a "; # Rfam3D
    $process_cmd .= "$dir";
    print FILE "$process_script $process_cmd\n\n";
    create_sh_file($N_Rfam3D,  \@Rfam3D,         $param, $paramfile, $dir, $shfile, \@trustedRfam3D,         0);

    #boostrap
   $shfile = "$my_shscripts/m8_fold_boostrap_cyk_simfold_$param.sh";
    print FILE "sh $shfile\n";
    $process_cmd = "";
    $process_cmd .= "-s "; # scores
    $process_cmd .= "-T "; # no mpi
    $process_cmd .= "-b "; # boostrap
    $process_cmd .= "$dir";
    print FILE "$process_script $process_cmd\n\n";
   create_sh_file($Nboostrap, \@boostrap,       $param, $paramfile, $dir, $shfile, \@trustedboostrap,       0);
    
    $shfile = "$my_shscripts/m8_fold_Rfam3D_boostrap_cyk_simfold_$param.sh";
    print FILE "sh $shfile\n";
    $process_cmd = "";
    $process_cmd .= "-s "; # scores
    $process_cmd .= "-T "; # no mpi
    $process_cmd .= "-a "; # Rfam3D
    $process_cmd .= "-b "; # boostrap
    $process_cmd .= "$dir";
    print FILE "$process_script $process_cmd\n\n";
    create_sh_file($Nboostrap, \@boostrapRfam3D, $param, $paramfile, $dir, $shfile, \@trustedboostrapRfam3D, 0);

    my @shfile_jacknife;
    for (my $j = 1; $j <= 3; $j ++) {
	$shfile_jacknife[$j] = "$my_shscripts/m8_fold_jacknife$j\_cyk_simfold_$param.sh";
	print FILE "sh $shfile_jacknife[$j]\n";
	$process_cmd = "";
	$process_cmd .= "-j $j "; # jacknife
	$process_cmd .= "-s ";    # scores
	$process_cmd .= "-T ";    # no mpi
	$process_cmd .= "$dir";
	print FILE "$process_script $process_cmd\n\n";
    }
    close(FILE);
    
  
      
    for (my $j = 1; $j <= 3; $j ++) {
	my @test;
	if ($j == 1) { @test = @trustedjacknife1RNA; }
	if ($j == 2) { @test = @trustedjacknife2RNA; }
	if ($j == 3) { @test = @trustedjacknife3RNA; }
	
	create_sh_file($N, \@RNA, $param, $paramfile, $dir, $shfile_jacknife[$j], \@test, $j, 0);
    }   
}
    
sub create_sh_file {
    my ($N, $RNA_ref, $param, $paramfile, $dir, $shfile, $typeRNA_ref, $jacknife) = @_;

    my $lexeme;
    my $testRNA;
    my $stofile;
    my $outfile;

    open(SH, ">$shfile");
    print SH "\#!/bin/sh\n";

    print SH "cd $dir\n\n";
    
    $lexeme = "$head\_$Gname\_fold\_$foldtype";
    for (my $t = 0; $t < $N; $t ++) {
	
	$testRNA = $RNA_ref->[$t];
	
	$stofile  = ($jacknife)? "$testRNA\_fold\_jacknife$jacknife\_$foldtype.sto"  : "$testRNA\_fold\_$foldtype.sto";
	$outfile  = ($jacknife)? "$testRNA\_fold\_jacknife$jacknife\_$foldtype.out"  : "$testRNA\_fold\_$foldtype.out";

	#command line
	my $cmd = "$simfold_script ";
	#option (the parameter set used)
	$cmd .= "-p $paramfile ";
	#arguments
	$cmd   .= "$typeRNA_ref->[$t] $stofile > $outfile";
	
	print SH "\#$testRNA\n";
	print SH "rm $lexeme.o*\n";
	print SH "rm $lexeme.po*\n";
	print SH "qsub -N $lexeme $qsub_cmd -o $dir '$cmd'\n";	
	print SH "\n";
    }
     close(SH);

    if ($verbose) { system("more $shfile\n"); }

}
