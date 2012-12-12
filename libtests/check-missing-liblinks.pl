#!/usr/bin/perl -w
#
use strict;

my @dirs = qw(/usr/lib64/ /lib64/);
my %checked;

for my $dir (@dirs)
{
	my @files = `ls $dir/*.so*`;
	for my $file ( @files )
	{
		chomp $file;
		my $base = $file;
		$base =~ s/so\.(.*?)$/so/g;
		next if exists $checked{$base};
		$checked{$base} = 1;
		if ( ! -f $base ) {
			print "missing base $base\n";
		}
	}
}
