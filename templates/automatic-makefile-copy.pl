#!/usr/local/bin/perl
eval 'exec /usr/bin/perl -S $0 ${1+"$@"}'
if 0; #$running_under_some_shell
 
  # Set the variable $File::Find::dont_use_nlink if you're using AFS,
  # since AFS cheats.
  
use strict;

#get arguments and needed infos  
  
  my $dir_workspace;
if(@ARGV[0])
{
  $dir_workspace=@ARGV[0];
}
else
{
  print "Please tell me the main directory of your C++ Library: ";
  chomp ($dir_workspace=<STDIN>);
  print "main directory: $dir_workspace !\n";
}

my $dir_template;
if(@ARGV[1])
{
  $dir_template=@ARGV[1];
}
else
{
  print "Please tell me the main directory of your Makefile templates C++/Make Directory: ";
  chomp ($dir_template=<STDIN>);
  print "Makefile template directory: $dir_template !\n";
}


my $is_sublib;
if(@ARGV[2])
{
  $is_sublib=@ARGV[2];
}
else
{
  print "Is your library is a sublibrary? (yes/no): ";
  chomp ($is_sublib=<STDIN>);
  print "Sub-Library: $is_sublib !\n";
}
$is_sublib = ($is_sublib =~ /yes/i);


my $scriptmode;
if(@ARGV[3])
{
  $scriptmode=@ARGV[3];
}
else
{
  print "Scriptmode (copy commands only)? (yes/no): ";
  chomp ($scriptmode=<STDIN>);
  print "Scriptmode: $scriptmode !\n";
}
$scriptmode = ($scriptmode =~ /yes/i);


my $simulation;
if(@ARGV[4])
{
  $simulation=@ARGV[4];
}
else
{
  print "Please tell me if you want to do a simulation? (yes/no): ";
  chomp ($simulation=<STDIN>);
  print "Simulation: $simulation !\n";
}
$simulation = ($simulation =~ /yes/i);

  #help
  if(!$scriptmode)
  {
    print "Makefile distribution tool for Libraries and its Sub-Libraries.\n";
    print "argument 1: Path to your Library\n";
    print "argument 2: Path to your Makefile Templates\n";
    print "argument 3: Distribute Makefiles in a Sub-Library (yes/no)\n";
    print "argument 4: Script Mode (copy commands only) (yes/no)\n";
    print "argument 5: Simulation (yes/no)\n\n";    
  }
  
  
#real work

&searchDirectory($dir_workspace);

sub searchDirectory {
  my $dir;
  my @lines;
  my $subdir;
  my $line;
  
  $dir = $_[0];
  #buggy if on, with $last_dir ASK ERIC
  if(!$scriptmode) 
    {
      print "current directory:$dir \n";
    }
  checkdirectory($dir);
  # check for permission
  if(-x $dir) {
    
    # search any sub directories
    @lines = `cd $dir; ls -l`;
    foreach $line (@lines) {
      if($line =~ /^d/) {
        $line =~ /\s+(\S+)$/;
        $subdir = $dir."/".$1;
        searchDirectory($subdir);
      }
    }
  }
}

sub checkdirectory{
  my $dir;
  my $last_dir;
  
  
#important: files to copy and directories to handle/ignore
  my @filenames=(["/progs/Makefile.inc"],["/tests/Makefile.inc"],["/sublib/Makefile.inc","/sublib/Makefile"]);
  #directories to handle
  my @dirnames=("progs","tests");
  #directories to ignore
  my @dirnames_ignore=("CVS","BUILD","templates","doc");
  
  
  #get current directory and extract last part of the current directory
  $dir = $_[0];
  if ( $dir =~ /\/([^\/]+)\/?$/ )
  {
    $last_dir=$1;
  } else {
    die ("unable to parse $dir\n");
  }
#   print "$last_dir\n";
  #compare to template specs
  
  my $count=0;
  my $found=0;
  #check ignored directories
  foreach my $possible_dir (@dirnames_ignore)
  {
    
    if ($is_sublib)
    {
    #sublib case
    }
    else #maindirectory is ignored
    {
      if (($found==0) && ($dir eq $dir_workspace))
      {
        if(!$scriptmode)
        {
          print "subdirectory_type: Ignored Main Directory\n";
        }
        $found=1;
      }
    }
    if (($found==0) && ($dir =~ /$dir_template/))
    {
      if(!$scriptmode)
      {
        print "subdirectory_type: Ignored Template Directory\n";
      }
      $found=1;
    }
    if (($found==0) && ($dir =~ /$possible_dir/))
    {
      if(!$scriptmode)
      {
        print "subdirectory_type: Ignored Subdirectory $possible_dir\n";
      }
      $found=1;
    }
  }
  #check if last directory corresponds to correct directories and do sth.
  
 
  foreach my $possible_dir (@dirnames)
  {
#         print "$found $last_dir $possible_dir\n";
    if(($found==0) && ($last_dir eq $possible_dir))
    {
      if(!$scriptmode)
      {
        print "subdirectory_type: $last_dir\n";
      }
      #do what has to be done
      foreach my $filename_entry(@{$filenames[$count]})
      {
        my $filename_tmp="$dir_template$filename_entry";
        if($simulation)
        {
          if($scriptmode)
          {
            print "cp $filename_tmp $dir\n";
          }
          else
          {
            print "simulation: cp $filename_tmp $dir\n";
          }
        }
        else
        {
          if($scriptmode)
          {
            print "cp $filename_tmp $dir\n";
          }
          else
          {
            print "copying: cp $filename_tmp $dir\n";
          }
          `cp $filename_tmp $dir`;
        }
      }
      $found=1;
    }
    $count++;
  }
  #normal library case
  if ($found==0)
  {
    if(!$scriptmode)
    {
      print "subdirectory_type: sublibrary\n";
    }
    foreach my $filename_entry(@{$filenames[$count]})
      {
        my $filename_tmp="$dir_template$filename_entry";
        if($simulation)
        {
          if($scriptmode)
          {
            print "cp $filename_tmp $dir\n";
          }
          else
          {
            print "simulation: cp $filename_tmp $dir\n";
          }
        }
        else
        {
          if($scriptmode)
          {
            print "cp $filename_tmp $dir\n";
          }
          else
          {
            print "copying: cp $filename_tmp $dir\n";
          }
          `cp $filename_tmp $dir`;
        }
      }
      $found=1;
  }
  if(!$scriptmode)
  {
    print "\n";  
  }
}




