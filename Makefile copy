EXEC = tester

CC = g++

CFLAGS = -std=c++20 -Wall -MMD -g -I/Library/Frameworks/SDL2.framework/Headers -I/Library/Frameworks/SDL2_image.framework/Headers -I/Library/Frameworks/SDL2_ttf.framework/Headers -F/Library/Frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf -rpath /Library/Frameworks


SRC = $(wildcard *.cc)

OBJECTS = $(SRC:.cc=.o)

DEPENDS = ${OBJECTS:.o=.d}

%.o: %.cc
	$(CC) $(CFLAGS) -c $< -o $@

${EXEC}: ${OBJECTS}
		${CC} ${CFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm *.o *.d ${EXEC}