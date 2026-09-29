CC ?= cc
AR ?= ar
CFLAGS ?= -O2 -Wall -Wextra -pedantic
CPPFLAGS ?= -Isrc -Iinclude

.PHONY: all test clean validate
all: build/amposix build/libamposix.a
build:
	mkdir -p build
build/amposix: src/amposix.c src/output.c src/output.h src/features.h src/headers.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ src/amposix.c src/output.c
build/lib_features.o: lib/features.c include/amposix/features.h src/features.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/features.c
build/libamposix.a: build/lib_features.o
	$(AR) rcs $@ $^
build/test_scan: tests/test_scan.c | build
	$(CC) $(CFLAGS) -o $@ tests/test_scan.c
build/test_database: tests/test_database.c src/features.h src/headers.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_database.c
build/test_lib_features: tests/test_lib_features.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_features.c build/libamposix.a
validate: build/test_database
	./build/test_database
test: build/amposix build/test_scan build/test_database build/test_lib_features
	./build/test_database
	./build/test_scan
	./build/test_lib_features
clean:
	rm -rf build
