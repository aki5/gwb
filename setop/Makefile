LIB =  ../lib/setoplib.a

SRC =  contfp.c dosetopgen.c dovertexonf.c inside.c sectors.c\
       separ.c setop.c setopcl.c setopgen.c setopgetnbr.c\
       sinsert.c srecledges.c sreclsectors.c\
       updmaxnames.c vtxfaccl.c vtxvtxcl.c\
       setopconnect.c ssortedges.c setopfinish.c

$(LIB):                $(SRC)
       csh -f Update $(LIB) $?

testsetop:     $(LIB) ../lib/splitlib.a ../lib/gwblib.a testsetop.o
       cc -g -o testsetop testsetop.o $(LIB) ../lib/splitlib.a \
               ../lib/gwblib.a -lm

c.o:;
       cc -c -g -DTEST $*.c
