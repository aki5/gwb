LIB =  ../lib/splitlib.a

SRC =  block.c classify.c cleanup.c dist.c getnbrhd.c insertnlledg.c \
       joincut.c missing.c neighbor.c recledges.c reclsectors.c \
       sortedges.c split.c splitclassif.c splitconnect.c splitfinish.c \
       splitgen.c sweep.c

$(LIB):                $(SRC)
       csh -f Update $(LIB) $?

splittest:     splittest.o $(LIB)
       cc -o splittest -g splittest.o $(LIB) ../lib/gwblib.a -lm

c.o:;
       cc -c -g -DTEST $*.c

