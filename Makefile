CC := g++
CFLAGS := -O2 -Wall -Wextra
SOURCES := ./source/*.cpp
LDFLAGS := -I./include/

logiccalc: logiccalc.cpp $(SOURCES)
	$(CC) $(CFLAGS) $< $(SOURCES) -o $@ $(LDFLAGS)

.PHONY: test clean

test: logiccalc
	./logiccalc "5 < (6<77) || True"

clean:
	rm -f ./logiccalc