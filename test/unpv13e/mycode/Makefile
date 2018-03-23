include ../Make.defines

PROGS = tcpcli01 tcpserv01

all: 	${PROGS}

tcpserv01: tcpserv01.o
	${CC} ${CFLAGS} -o $@ tcpserv01.o ${LIBS}

tcpcli01: tcpcli01.o
	${CC} ${CFLAGS} -o $@ tcpcli01.o ${LIBS}

clean:
	rm -f *.o
	rm -f ${PROGS}
