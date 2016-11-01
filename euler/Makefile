LIB =  ../lib/gwblib.a

SRC =  addhe.c addlist.c arc.c bndrlv.c circle.c contlv.c contvv.c del.c \
       delhe.c dellist.c faceeq.c init.c int2ee.c intrve.c kef.c kev.c \
       larea.c listsolid.c lkef.c lkemr.c lkev.c lkfmrh.c \
       lmef.c lmekr.c lmev.c lmfkrh.c loopglue.c mef.c mev.c mvfs.c new.c \
       revert.c rsweep2.c scan.c scannames.c solidls.c svolume.c torus.c\
       laringmv.c contfv.c merge.c checkv.c vector.c

$(LIB):                $(SRC)
       csh -f Update $(LIB) $?

test5:         test5.c $(LIB)
       cc -o test5 test5.c -g $(LIB) -lm

test3:         test3.c $(LIB)
       cc -o test3 test3.c -g $(LIB) -lm

test2:         test2.c $(LIB)
       cc -o test2 test2.c -g $(LIB)

test1:         test1.c $(LIB)
       cc -o test1 test1.c -g $(LIB)

c.o:;
       cc -c -g -DTEST $*.c
