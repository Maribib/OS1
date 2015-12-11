CFLAGS = -Wall -Wextra
CC := G++

all: simAudsley taskGenerator studyAudsley


simAudsley: 
	${CC} -o $@ simulator/*.cpp datastructure/*.cpp pattern/*.cpp ${LDFLAGS}

taskGenerator: 
	${CC} -o $@ generator/*.cpp datastructure/*.cpp ${LDFLAGS}

studyAudsley:
	${CC} -o $@ study/*.cpp generator/Generator.cpp datastructure/*.cpp simulator/Ram.cpp simulator/S*.cpp simulator/TaskFileParser.cpp pattern/*.cpp ${LDFLAGS}

mrproper:
	rm simAudsley
	rm taskGenerator
	rm studyAudsley