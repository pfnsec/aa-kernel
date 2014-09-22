#!/usr/bin/perl

my $dir = $ENV{INCLUDE_DIR};

open (CFG_HEAD, "$dir/config_head.h") or die "Can't open $dir/config_head.h: $!\n";
open (CFG, ">$dir/config.h") or die "Can't open $dir/config.h: $!\n";
open (CFG_TAIL, "$dir/config_tail.h") or die "Can't open $dir/config_tail.h: $!\n";

for $line (<CFG_HEAD>) {
	print CFG "$line";
}

while(my $cfgline = <>) {
	$cfgline =~ "^([^= ]+)[ ]*=[ ]*([^\n]+)";
	next if $1 eq "" or $2 eq "";
#	print  "#define $1 \"$2\"\n";
	print CFG "#define $1 $2\n";
}

for $line (<CFG_TAIL>) {
	print CFG "$line";
}
