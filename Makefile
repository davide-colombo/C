CC:= cc
CFLAGS:= -O2

trgs:= nlines nblanks
objs:= $(patsubst %,%.o,$(trgs))
asms:= $(patsubst %,%.s,$(trgs))

# Targets
$(trgs): %: %.o
	$(CC) $(CFLAGS) -o $@ $<

# Object files
$(objs): %.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Creates the assembly file for inspection
$(asms): %.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $<

# Use a pattern matching rule that does not have prerequisites (nothing after the second colon);
# Use the "$*" to take the stem (i.e., the part that corresponds to the '%');
cl%: %.c
	rm -f $* $*.o $*.s
