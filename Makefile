SRC = arg.c io.c main.c
OBJ = ${SRC:.c=.o}
CC = tcc
CFLAGS = -Wall

%.o: %.c
	${CC} -c $^ -o $@

tkt: ${OBJ}
	${CC} ${OBJ} ${CFLAGS} ${LDFLAGS} -o $@

clean:
	rm -f tkt ${OBJ}

install: tkt
	mkdir -p ./bin
	mv -f tkt ./bin
