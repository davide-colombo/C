
test: strstat.o test.o
	cc $^ -o $@

test.o: test.c
	cc -c test.c -o test.o

strstat.o: strstat.c
	cc -c strstat.c -o strstat.o

clean:
	rm -f strstat.o test.o test

