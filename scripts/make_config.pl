#!/usr/bin/perl

use File::Find;

my %cfg_table = ();

my $src_list = "";

open (CFG_IN, "<config") or die "Can't open config: $!\n";

open (CFG_HEAD, "<src/include/config_head.h") or die "Can't open src/include/config_head.h: $!\n";

open (CFG, ">src/include/config.h") or die "Can't open src/include/config.h: $!\n";

open (CFG_TAIL, "<src/include/config_tail.h") or die "Can't open src/include/config_tail.h: $!\n";

open (CFG_MK, ">config.out.mk") or die "Can't open config.out.mk: $!\n";

opendir (SRC, "src");

for $line (<CFG_HEAD>) {
	print CFG "$line";
}

while(my $cfgline = <CFG_IN>) {
	$cfgline =~ "^([^= ]+)[ ]*=[ ]*([^\n]+)";

	next if $1 eq "" or $2 eq "";

	$cfg_table { $1 } = $2;

	print CFG "#define $1 $2\n";
	print CFG_MK "export $1=$2\n";
}

for $line (<CFG_TAIL>) {
	print CFG "$line";
}

sub add_sources {
	my $prefix = shift;
	my @sources = ();
	open (my $src_cfg, "<$prefix/sources.config");

	#match a key=value pair, followed by a number of sources files/directories
	KEYVAL: while(my $src_cfg_keyval = <$src_cfg>) {
		if(($src_cfg_keyval =~ "^([^= ]+)[ ]*=[ ]*([^\n]+):") or ($src_cfg_keyval eq "all:\n")) {

			#if the config variable matches the value required by sources.config, include the source files
			if(($cfg_table{$1} eq $2) or ($src_cfg_keyval eq "all:\n")) {
				while($src_cfg_file = <$src_cfg>) {

					#if this doesn't match the file regex, we assume this is a new config variable specifier
					$src_cfg_keyval = $src_cfg_file;

					chomp $src_cfg_file;
					if ($src_cfg_file =~ "^\tinc ([^ ]+)") {
						print "inc ($1)\n";
						print CFG_MK "export C_INCLUDE_PATH:=\$(C_INCLUDE_PATH):$prefix/$1\n";
						add_sources("$prefix/$1");
					} elsif($src_cfg_file =~ "\t([^ ]+(\.c|\.S))") {
#						print "src($1)\n";
						push(@sources, "$prefix/$1");
					} elsif ($src_cfg_file =~ "^\tdir ([^ ]+)") {
#						print "dir ($1)\n";
						add_sources("$prefix/$1");
					} else {
#						print "neither ($1)!\n";
						redo KEYVAL;
					}
				}
			}
		}
	}

	my %seen_files = ();
	my @unique_sources = ();

	foreach my $file ( @sources ) {
		next if $seen_files{ $file }++;

		push (@unique_sources, $file);
	}

	print "@unique_sources\n";

	if(@unique_sources != ()) {
		print CFG_MK "export SOURCES+=@unique_sources\n";
	}
}

add_sources("src");


