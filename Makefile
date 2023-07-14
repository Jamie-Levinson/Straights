CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = straights
OBJECTS = card.o deck.o player.o subject.o gamemodel.o gameview.o main.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
