CFLAGS = -Wall -Wextra
CC := G++

all: simAudsley taskGenerator


simAudsley: 
	${CC} -o $@ simulator/*.cpp datastructure/*.cpp ${LDFLAGS}

taskGenerator: 
	${CC} -o $@ generator/*.cpp ${LDFLAGS}

clean:
	rm simAudsley
	rm taskGenerator