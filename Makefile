SRC_DIR		:= src
INC_DIR		:= ${SRC_DIR}/include
OBJ_DIR		:= ${SRC_DIR}/obj

CC			:= g++
CFLAGS		:= -I${INCLUDE_DIR}

_OBJS	 	:= main.o tree.o customErrorClass.o		# List of created object files
OBJS		:= ${patsubst %, ${OBJ_DIR}/%, ${_OBJS}}# Generics for file names

.PHONY: clean all

all: Bauer_CodeChallenge2

# Removes the old files.
clean:
	rm ${OBJS} Bauer_CodeChallenge2

# Creates the object files.
${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	${CC} -c -o $@ $< ${CFLAGS}

# Creates the executable.
Bauer_CodeChallenge2: ${OBJS}
	${CC} -o $@ $^ ${CFLAGS}
