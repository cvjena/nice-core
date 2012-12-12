#!/usr/bin/perl -w


for my $file ( @ARGV )
{
	my $namespace_found = 0;
	open ( FILE, "<$file" ) or die ("$file: $!\n");

	while (<FILE>)
	{
		chomp;
		if ( /^ *namespace +/ ) {
			$namespace_found = 1;
		}
		if ( /^ *#include/ && ! /\.tcc/ ) {
			if ( $namespace_found ) {
				warn("$file: wrong order of namespace and includes!\n");
				last;
			}
		}
	}

	close ( FILE );
}
