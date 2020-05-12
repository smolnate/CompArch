all: readfile

readfile: read.c
	gcc -Wall -Werror -fsanitize=address -std=c11 read.c -o readfile

clean:
	rm -f readfile
