
CC       = gcc
CFLAGS   = -g -Wall
LIBS     = -leasel -lm
LFLAGS   = -L ~/src/easel
IFLAGS   = -I ~/src/easel

PROGS    = milestone1\
	   m2_collate\
	   m2_fold\
	   m2_train\
	   m3_train\
	   sseval

OBJS     = cyk.o\
	   grammar.o\
	   grammar_io.o\
	   nussinov.o\
	   parsetree.o\
	   sscyk.o\
	   util.o

HDRS     = cyk.h\
	   grammar.h\
	   grammar_io.h\
	   nussinov.h\
	   parsetree.h\
	   sscyk.h\
	   util.h

.c.o:
	${CC} ${IFLAGS} ${CFLAGS} -c $<


all: ${PROGS} ~/src/easel/libeasel.a

${PROGS}: %: %.o ${OBJS}
	${CC} ${CFLAGS} ${IFLAGS} ${LFLAGS} -o $@ $@.o ${OBJS} ${LIBS}

clean:
	rm *.o *~ ${PROGS}

backup:
	( cd .. ; rsync -avuzb tornado/ wrasse:src/tornado/ )

tags:
	etags Makefile *.c *.h
