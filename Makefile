CC = gcc
DEBUG = -g
DEFINES = 
DEPENDS = monitorasaurus.h
CFLAGS = $(DEBUG) -Wall -Wextra -Wshadow -Wunreachable-code \
	-Wredundant-decls -Wmissing-declarations \
	-Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wno-return-local-addr \
	-Wunsafe-loop-optimizations -Wuninitialized -Werror \
	-Wno-unused-parameter $(DEFINES)
PROG = monitorasaurus

all: $(PROG)

$(PROG): $(PROG).o
	$(CC) $(CFLAGS) -o $@ $^  

$(PROG).o: $(PROG).c $(DEPENDS)
	$(CC) $(CFLAGS) -c $< 
 
clean cls:
	rm -f $(PROG) *.o *~ \#*

tar:
	tar cvfa monitorasaurus_${LOGNAME}.tar.gz monitorasaurus.c monitorasaurus.h [mM]akefile

git-checkin:
	if [ ! -d .git ] ; then git init; fi
	git add *.[ch] ?akefile
	git commit -m "automatic commit"






