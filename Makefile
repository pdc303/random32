random32: random32.c
	gcc -Wall -O2 $^ -o $@

clean:
	rm -f random32
