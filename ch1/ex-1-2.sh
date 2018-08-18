#!/bin/sh

ofile=ex-1-2.c
exec 1>$ofile
echo '#include <stdio.h>

int
main(void)
{
'
echo -n '	printf("'
for i in `seq 1 128`
do
	octal=`printf "%03o" $i`
	char="$(printf "%b" "\\$octal")"
	case "$char" in
	x|u|U) ;;
	*) echo -n "\\$char"
	esac
done
echo '");
}'
