
CC:= cc
CFLAGS:= -O2

trgs:= nlines
objs:= $(wildcard $(trgs)*.o)
asms:= $(wildcard $(trgs)*.s)

# Targets
$(trgs): %: %.o

# Object files
$(objs): %.o: %.c

# Creates the assembly file for inspection
$(trgs).s: %.s: %.c
	$(CC) $(CFLAGS) -S -o $@ $<

# Creates one target for each element in the "trgs" variable;
# Use a pattern matching rule that does not have prerequisites (nothing after the second colon);
# Use the "$*" to take the stem (i.e., the part that corresponds to the '%');
clean_$(trgs): clean_%:
	rm -f $* $*.o $*.s
