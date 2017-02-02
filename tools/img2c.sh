#!/bin/bash

if [ $# -lt 1 ]; then
	echo "Usage: $0 imgfile" > /dev/stderr
	exit 1
fi

src=$1
name=${src%.*}
geo=$(identify $src | cut -d' ' -f3)
name_u=$(echo $name | tr '[:lower:]' '[:upper:]' | tr '.' '_')

echo "#define ${name_u}_WIDTH $(echo $geo | cut -d'x' -f1)"
echo "#define ${name_u}_HEIGHT $(echo $geo | cut -d'x' -f2)"

convert $src -depth 8 ${name}.bgra
xxd -i ${name}.bgra | head -n -1
