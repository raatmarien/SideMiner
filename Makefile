VPATH = src
CC = g++
CFLAG = -I headers --std=c++11
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
OBJ = main.o            \
      chunk.o           \
      chunkManager.o    \
      midpointDisplacement.o
HEADERS = $(wildcard headers/*.h)
EXEC = sideMiner

all : sideMiner

%.o : %.cpp
	$(CC) -c $< -o $@ $(CFLAG)

sideMiner : $(OBJ) $(HEADERS)
	$(CC) -o $(EXEC) $(OBJ) $(LIBS)

.PHONY : clean
clean :
	rm $(EXEC) $(OBJ)
