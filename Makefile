CC = gcc
CFLAGS = -Wall -W -pedantic `sdl-config --cflags`
CLIBS = -L/usr/X11R6/lib -lGL `sdl-config --libs` -lm -lpng -lSDL_mixer

wayang: main.o texture.o mesh3d.o wayang.o movements.o
	$(CC) $(CLIBS) *.o -o wayang
	mv wayang ../
main.o: main.c mesh3d.h texture.h wayang.h
	$(CC) $(CFLAGS) main.c -c
texture.o: texture.c texture.h
	$(CC) $(CFLAGS) texture.c -c
mesh3d.o: mesh3d.c mesh3d.h
	$(CC) $(CFLAGS) mesh3d.c -c
wayang.o: wayang.h wayang.c movements.h
	$(CC) $(CFLAGS) wayang.c -c
movements.o: movements.c movements.h
	$(CC) $(CFLAGS) movements.c -c

clean:
	@echo Cleaning up...
	@rm -f *.o *~ core*
	@echo Done.
