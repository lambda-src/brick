use strict;
use warnings;
use File::Find;

find(sub {
    # ensure its a file and not the curr file
    return unless -f $_ && $_ ne "todo.pl";
    open my $fh, $_ or die "Couldn't open file";
    while (my $line = <$fh>) {
        next unless $line =~ /TODO:/;
        $line =~ s/^\s+|\s+$//g;
        print "$File::Find::name:$.: $line\n";
    }
    close $fh;
}, ".");
