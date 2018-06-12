
lsd:
the Linux Simple Dump command dumps decimal or hexadecimal values of file and each
printable character. An # char substitutes each no printable char.
Newline and tab characters are represented by "\n" and "\t" respectively 

Usage:
lsd [options] file

Options:
    -h          Prints this help
    -b N        Dump only N rows of 8 bytes
    -d          Print output values in decimal
    -x          Print output values in hexadecimal
If no options are introduced, lsd dumps the entire file with decimal values

Examples:
lsd -x -d -b 10 /etc/dictionaries-common/words
output the 80 first bytes in "words" file in decimal and hexadecimal form

lsd is released, with no warranty, under the GPL license. Feel free to copy, 
modify or redistribute it

Please send comments, reports and contributions to https://github.com/aljito/lsd
lsd version 1.10
(C) 2018 A.Jimenez

