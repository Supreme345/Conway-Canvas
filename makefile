CC = g++

CFLAGS = -c `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

all : 		life_grid 

life_grid : 	main.o life_grid.o
		@echo "Link and producing the final application"
		$(CC) main.o life_grid.o -o life_grid $(LDFLAGS)

life_grid.o:	life_grid.cpp
		@echo "Compiling the life_grid.cpp file"
		$(CC) -c life_grid.cpp $(CFLAGS)

main.o	:	main.cpp
		@echo "Compiling the main.cpp file"
		$(CC) -c main.cpp $(CFLAGS)

clean 	:	
		@echo "Removing everything except the source file"
		rm main.o life_grid.o life_grid
