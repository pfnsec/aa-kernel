#!/usr/bin/perl

open (CFG_IN, "<config") or die "Can't open config: $!\n";
open (CFG_HEAD, "<src/include/config_head.h") or die "Can't open src/include/config_head.h: $!\n";
open (CFG, ">src/include/config.h") or die "Can't open src/include/config.h: $!\n";
open (CFG_TAIL, "<src/include/config_tail.h") or die "Can't open src/include/config_tail.h: $!\n";
open (CFG_MK, ">config.out.mk") or die "Can't open config.out.mk: $!\n";

for $line (<CFG_HEAD>) {
	print CFG "$line";
}

while(my $cfgline = <CFG_IN>) {
	$cfgline =~ "^([^= ]+)[ ]*=[ ]*([^\n]+)";
	next if $1 eq "" or $2 eq "";
	print CFG "#define $1 $2\n";
	print CFG_MK "export $1=$2\n";
}

for $line (<CFG_TAIL>) {
	print CFG "$line";
}
