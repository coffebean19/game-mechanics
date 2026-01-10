CC=gcc

C=main.c

CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -Llib -lraylib -lm -ldl -lGL -lX11

all: shooter

shooter:
	$(CC) $(C) -o program $(CFLAGS) $(LDFLAGS)

clean:
	rm -f program