CC := gcc
CFLAGS := -O2 -Wall -Wextra
SOURCES := ./source/*.c
LDFLAGS := -I./include/

logiccalc: logiccalc.c $(SOURCES)
	$(CC) $(CFLAGS) $< $(SOURCES) -o $@ $(LDFLAGS)

.PHONY: test clean

test:
	./logiccalc "!(!5<5->5<=5)>5"

clean:
	rm -f ./logiccalc