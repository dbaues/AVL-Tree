INCLUDE_DIR	:= include
CC			:= g++
CFLAGS		:= -I${INCLUDE_DIR}

OBJS	 	:= main.o tree.o customErrorClass.o
DEPS_CEC	:= ${INCLUDE_DIR}/customErrorClass.h	# Path to customErrorClass.h
DEPS_TREE	:= ${INCLUDE_DIR}/tree.h				# Path to tree.h

.PHONY: clean all

all: Bauer_CodeChallenge2

# Removes the old files.
clean:
	rm ${OBJS} Bauer_CodeChallenge2

# Creates the object files.
customErrorClass.o: customErrorClass.cpp ${DEPS_CEC}
	${CC} -c -o $@ ${CFLAGS} $<

tree.o: tree.cpp ${DEPS_TREE}
	${CC} -c -o $@ ${CFLAGS} $<

main.o: main.cpp ${DEPS_TREE}
	${CC} -c -o $@ ${CFLAGS} $<

# Creates the executable.
Bauer_CodeChallenge2: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}