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
build/lib_stdio.o: lib/stdio.c include/amposix/stdio.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/stdio.c
build/lib_string.o: lib/string.c include/amposix/string.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/string.c
build/lib_env.o: lib/env_host.c include/amposix/env.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/env_host.c
build/libamposix.a: build/lib_features.o build/lib_stdio.o build/lib_string.o build/lib_env.o
	$(AR) rcs $@ $^
build/test_scan: tests/test_scan.c | build
	$(CC) $(CFLAGS) -o $@ tests/test_scan.c
build/test_database: tests/test_database.c src/features.h src/headers.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_database.c
build/test_lib_features: tests/test_lib_features.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_features.c build/libamposix.a
build/test_lib_stdio: tests/test_lib_stdio.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_stdio.c build/libamposix.a
build/test_lib_string: tests/test_lib_string.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_string.c build/libamposix.a
build/test_lib_env: tests/test_lib_env.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_env.c build/libamposix.a
validate: build/test_database
	./build/test_database
test: build/amposix build/test_scan build/test_database build/test_lib_features build/test_lib_stdio build/test_lib_string build/test_lib_env
	./build/test_database
	./build/test_scan
	./build/test_lib_features
	./build/test_lib_stdio
	./build/test_lib_string
	./build/test_lib_env
clean:
	rm -rf build
