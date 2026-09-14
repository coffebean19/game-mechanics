CC=gcc

C=main.c

CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lraylib -lm -ldl -lGL -lX11

all: shooter sprite

shooter:
	$(CC) ./shooter/main.c -o shooter $(CFLAGS) $(LDFLAGS)

sprite:
	$(CC) sprite.c -o sprit $(CFLAGS) $(LDFLAGS)

clean:
	rm -f program
