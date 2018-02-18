#variables de compilation
SHELL := /bin/sh
CC    := gcc
CFLAGS += -O3 -flto -Wall -W -pedantic $(shell pkgconf gl sdl libpng SDL_mixer --cflags) -std=gnu90 -ffast-math -pipe
LDFLAGS +=  -L/usr/X11R6/lib $(shell pkgconf gl sdl libpng SDL_mixer --libs) -lm
TARGET   := wayang-by-cyberneticgenetics
#variable de nettoyage
RM_F := rm -f

#compilation en paralelle si disponible
ifneq (,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
 NUMJOBS = $(patsubst parallel=%,%,$(filter parallel=%,$(DEB_BUILD_OPTIONS)))
 MAKEFLAGS += -j$(NUMJOBS)
endif

export

all: $(TARGET)

$(TARGET): main.o texture.o mesh3d.o wayang.o movements.o
	$(CC) -flto *.o $(LDFLAGS) -o $(TARGET)
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
	-@$(RM_F) $(TARGET) *.o *~ core*
	@echo Done.
