CFLAGS = -Wall -Wextra
CC := G++

all: simAudsley taskGenerator studyAudsley


simAudsley: 
	${CC} -o $@ simulator/*.cpp datastructure/*.cpp ${LDFLAGS}

taskGenerator: 
	${CC} -o $@ generator/*.cpp datastructure/*.cpp ${LDFLAGS}

studyAudsley:
	${CC} -o $@ study/*.cpp ${LDFLAGS}

clean:
	rm simAudsley
	rm taskGenerator
	rm studyAudsley