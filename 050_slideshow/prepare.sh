#!/bin/bash

width=640

mkdir -p bgra
for img in $(ls img/*); do
	bgra="bgra/$(basename ${img%.*}).bgra"
	echo "img=$img, bgra=$bgra"
	convert $img -resize ${width}x -depth 8 $bgra
done
