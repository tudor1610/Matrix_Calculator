build: my_octave.c
	gcc -Wall -Wextra -std=c99 my_octave.c -o my_octave

clean:
	rm -f my_octave
.PHONY: pack clean