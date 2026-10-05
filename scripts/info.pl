use strict;
use warnings;
use File::Find;

my $lines = 0;
my %files;

find(sub {
    # skip entries that are dirs
    return unless -f $_;
    # get the extension and inc its count
    my ($ext) = $_ =~ /(\.[^.]+)$/;
    $files{$ext // "No EXT"}++;
    open my $file, $_ or die "Couldn't open file";
    $lines++ while <$file>;
    close $file;
}, "src");

print "Brick src code lines: $lines\n";

while (my ($key, $val) = each %files) {
    print "$val $key files\n";
}
