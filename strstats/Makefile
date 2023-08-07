
# The order in which arguments are passed matter!
test: test.o strstat.o stralloc.o
	cc $^ -o $@

test.o: test.c
	cc -c test.c -o test.o

strstat.o: strstat.c
	cc -c strstat.c -o strstat.o

stralloc.o: stralloc.c
	cc -c stralloc.c -o stralloc.o

clean:
	rm -f test *.o

