CC := g++
CFLAGS := -O2 -Wall -Wextra
SOURCES := ./source/*.cpp
LDFLAGS := -I./include/

logiccalc: logiccalc.cpp $(SOURCES)
	$(CC) $(CFLAGS) $< $(SOURCES) -o $@ $(LDFLAGS)

.PHONY: test test_ops test_wrong_input clean

test: logiccalc
	./logiccalc "!((1 > 2)->(1 > 3))" "!((2 > 2)->(2 > 3))" "!((3 > 2)->(3 > 3))" "!((4 > 2)->(4 > 3))"
	./logiccalc "(0 || 1) && (0 || 1) && ! 1 && ! 1" "(1 || 0) && (1 || 0) && ! 0 && ! 0"
	# "(a-> b && !c) && (c-> b && a) && (b-> c && a)" == "!a && !b && !c"
	./logiccalc "(1-> 1 && !1) && (1-> 1 && 1) && (1-> 1 && 1)" "(1-> 1 && !0) && (0-> 1 && 1) && (1-> 0 && 1)" "(1-> 0 && !1) && (1-> 0 && 1) && (0-> 1 && 1)" "(0-> 1 && !1) && (1-> 1 && 0) && (1-> 1 && 0)" "(0-> 0 && !0) && (0-> 0 && 0) && (0-> 0 && 0)"
	./logiccalc "!1 && !1 && !1" "!1 && !1 && !0" "!1 && !0 && !1" "!0 && !1 && !1" "!0 && !0 && !0"

test_wrong_input: logiccalc
	./logiccalc "((((1)"
	./logiccalc "(1))"
	./logiccalc "<55"
	./logiccalc "55<"
	./logiccalc "55 < 55 ||"
	./logiccalc "(55 < 55) || "
	./logiccalc "(55 < 55) <= 55 ||"
	./logiccalc "5 < < 6"
	./logiccalc "5 < || 6"
	./logiccalc "0 < 1 0"
	./logiccalc "0 || 1 !"
	./logiccalc "0 || 1 -"

test_ops: logiccalc
	./logiccalc "0"
	./logiccalc "1"
	./logiccalc "5 < 6"
	./logiccalc "6 < 5"
	./logiccalc "6 < 6"
	./logiccalc "5 <= 6"
	./logiccalc "6 <= 6"
	./logiccalc "6 <= 5"
	./logiccalc "6 > 5"
	./logiccalc "5 > 6"
	./logiccalc "6 > 6"
	./logiccalc "6 >= 5"
	./logiccalc "6 >= 6"
	./logiccalc "5 >= 6"
	./logiccalc "5 == 5"
	./logiccalc "5 == 6"
	./logiccalc "5 != 6"
	./logiccalc "6 != 6"
	./logiccalc "0 && 0"
	./logiccalc "0 && 1"
	./logiccalc "1 && 0"
	./logiccalc "1 && 1"
	./logiccalc "0 || 0"
	./logiccalc "0 || 1"
	./logiccalc "1 || 0"
	./logiccalc "1 || 1"
	./logiccalc "0 ^ 0"
	./logiccalc "0 ^ 1"
	./logiccalc "1 ^ 0"
	./logiccalc "1 ^ 1"
	./logiccalc "0 -> 0"
	./logiccalc "0 -> 1"
	./logiccalc "1 -> 0"
	./logiccalc "1 -> 1"
	./logiccalc "! 0"
	./logiccalc "! 1"

clean:
	rm -f ./logiccalc