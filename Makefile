TARGET=ascii
CFLAGS=-Wall -Wextra -Wpedantic

FILES=$(basename $(wildcard *.c))
SOURCES=$(addsuffix .c, $(FILES))
OBJECTS=$(addsuffix .o, $(FILES))

all: $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $?

$(OBJECTS): %.o : %.c
	$(CC) -o $@ -c $(CFLAGS) $(CPPFLAGS) $<
