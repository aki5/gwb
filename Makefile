libs:
       cd euler; make
       cd split; make
       cd setop; make

c.o:;
       cc -c -g -DTEST $*.c
