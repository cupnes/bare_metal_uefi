#!/bin/bash

width=640
dst=img

for orig in $@; do
	new="$dst/$(basename ${orig%.*}).png"
	echo "orig=$orig, new=$new"
	convert $orig -resize ${width}x $new
done
