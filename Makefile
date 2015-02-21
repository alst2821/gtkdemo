CFLAGS += `pkg-config --cflags gtk+-3.0`
LDLIBS += `pkg-config --libs gtk+-3.0`


test: test.o

hh: hh.o



