CFLAGS += -g -Wall `pkg-config --cflags gtk+-3.0` 
LDLIBS += `pkg-config --libs gtk+-3.0` -lm

color_CFLAGS =+ -DCOLOR

test: test.o color.o

color: color.o

hh: hh.o



