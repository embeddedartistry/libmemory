#!/bin/bash


find . -type d \( -path ./dependencies/ \) -prune \
	-iname *.h -o -iname *.c -o -iname *.cpp -o -iname *.hpp \
	| xargs clang-format -style=file -i -fallback-style=none

exit 0
