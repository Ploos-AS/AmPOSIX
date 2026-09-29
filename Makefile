CC ?= cc
CFLAGS ?= -O2 -Wall -Wextra -pedantic
CPPFLAGS ?= -Isrc

.PHONY: all test clean
all: build/amposix
build:
	mkdir -p build
build/amposix: src/amposix.c src/output.c src/output.h src/features.h src/headers.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ src/amposix.c src/output.c
build/test_scan: tests/test_scan.c | build
	$(CC) $(CFLAGS) -o $@ tests/test_scan.c
test: build/amposix build/test_scan
	./build/test_scan
clean:
	rm -rf build
