
# The order in which arguments are passed matter!
test: test.o strstat.o strbytes.o
	cc $^ -o $@

test.o: test.c
	cc -c test.c -o test.o

strstat.o: strstat.c
	cc -c strstat.c -o strstat.o

strbytes.o: strbytes.c
	cc -c strbytes.c -o strbytes.o

clean:
	rm -f test *.o

