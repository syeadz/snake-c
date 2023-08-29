C_SOURCES = $(wildcard *.c)
HEADERS = $(*.h)

OBJ = ${C_SOURCES:.c=.o}

CC = gcc
CFLAGS = -Wextra -Wall
LIB = -lncurses
TARGET = snake

DEBUG_CFLAGS = -g -DDEBUG

${TARGET}: ${OBJ}
	$(CC) ${LIB} $^ -o $@


run: ${TARGET}
	./$^

clean:
	rm -rf *.o ${TARGET}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} ${DEBUG_CFLAGS} -c $< -o $@