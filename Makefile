CC=gcc
CFLAGS=-Wall

LDFLAGS=`pkg-config allegro-5 allegro_font-5 --libs --cflags`

src = $(wildcard src/*.c)
obj = $(src:.c=.o)

%.o: %.c 
	$(CC) $(CFLAGS) -c -g -o $@ $< 

debug: $(obj) 
	$(CC) $(CFLAGS) -g -I /usr/include/allegro -I ./src -o csnake $< $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(obj) csnake
