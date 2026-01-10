CC=gcc

C=main.c

CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lraylib -lm -ldl -lGL -lX11

all: game

game:
	$(CC) $(C) -o program $(CFLAGS) $(LDFLAGS)

clean:
	rm -f program