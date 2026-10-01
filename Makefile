CC ?= cc
AR ?= ar
CFLAGS ?= -O2 -Wall -Wextra -pedantic
CPPFLAGS ?= -Isrc -Iinclude

.PHONY: all test clean validate amiga-smoke amiga-qualification amiga-payload amiga-probes
all: build/amposix build/libamposix.a
build:
	mkdir -p build
build/amposix: src/amposix.c src/output.c src/output.h src/feature_db.h src/headers.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ src/amposix.c src/output.c
build/lib_features.o: lib/features.c include/amposix/features.h src/feature_db.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/features.c
build/lib_stdio.o: lib/stdio.c include/amposix/stdio.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/stdio.c
build/lib_string.o: lib/string.c include/amposix/string.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ lib/string.c
build/lib_env.o: lib/env.c include/amposix/env.h lib/platform.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c -o $@ lib/env.c
build/platform_host.o: platform/host/platform.c lib/platform.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c -o $@ platform/host/platform.c
build/lib_net.o: lib/net.c include/amposix/net.h lib/net_platform.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c -o $@ lib/net.c
build/net_platform_host.o: platform/host/net_platform.c lib/net_platform.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c -o $@ $<
build/lib_netdb.o: lib/netdb.c include/amposix/netdb.h lib/platform.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c -o $@ lib/netdb.c
build/lib_time.o: lib/time.c include/amposix/time.h lib/platform.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -Ilib -c -o $@ lib/time.c
build/libamposix.a: build/lib_features.o build/lib_stdio.o build/lib_string.o build/lib_env.o build/lib_time.o build/lib_netdb.o build/lib_net.o build/platform_host.o build/net_platform_host.o
	$(AR) rcs $@ $^
build/test_scan: tests/test_scan.c | build
	$(CC) $(CFLAGS) -o $@ tests/test_scan.c
build/test_database: tests/test_database.c src/feature_db.h src/headers.h | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_database.c
build/test_lib_features: tests/test_lib_features.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_features.c build/libamposix.a
build/test_lib_stdio: tests/test_lib_stdio.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_stdio.c build/libamposix.a
build/test_lib_string: tests/test_lib_string.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_string.c build/libamposix.a
build/test_lib_env: tests/test_lib_env.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_env.c build/libamposix.a
build/test_lib_net: tests/test_lib_net.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_net.c build/libamposix.a
build/test_lib_netdb: tests/test_lib_netdb.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_netdb.c build/libamposix.a
build/test_lib_time: tests/test_lib_time.c build/libamposix.a | build
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $@ tests/test_lib_time.c build/libamposix.a
validate: build/test_database
	./build/test_database
test: build/amposix build/test_scan build/test_database build/test_lib_features build/test_lib_stdio build/test_lib_string build/test_lib_env build/test_lib_net build/test_lib_netdb build/test_lib_time
	./build/test_database
	./build/test_scan
	./build/test_lib_features
	./build/test_lib_stdio
	./build/test_lib_string
	./build/test_lib_env
	./build/test_lib_net
	./build/test_lib_netdb
	./build/test_lib_time
clean:
	rm -rf build

AMIGA_CC ?= m68k-amigaos-gcc
AMIGA_AR ?= m68k-amigaos-ar
AMIGA_CFLAGS ?= -O2 -Wall -Wextra -pedantic
AMIGA_CPPFLAGS ?= -Iinclude -Ilib -Isrc
AMIGA_OBJECTS = build/amiga/lib_features.o build/amiga/lib_stdio.o build/amiga/lib_string.o build/amiga/lib_env.o build/amiga/lib_time.o build/amiga/lib_netdb.o build/amiga/lib_net.o build/amiga/platform.o

build/amiga:
	mkdir -p build/amiga
build/amiga/lib_features.o: lib/features.c include/amposix/features.h src/feature_db.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ lib/features.c
build/amiga/lib_stdio.o: lib/stdio.c include/amposix/stdio.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ lib/stdio.c
build/amiga/lib_string.o: lib/string.c include/amposix/string.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ lib/string.c
build/amiga/lib_env.o: lib/env.c include/amposix/env.h lib/platform.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ lib/env.c
build/amiga/lib_net.o: lib/net.c include/amposix/net.h lib/net_platform.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -Ilib -c -o $@ lib/net.c
build/amiga/lib_netdb.o: lib/netdb.c include/amposix/netdb.h lib/platform.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ lib/netdb.c
build/amiga/lib_time.o: lib/time.c include/amposix/time.h lib/platform.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ lib/time.c
build/amiga/platform.o: platform/amigaos/platform.c lib/platform.h | build/amiga
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -c -o $@ platform/amigaos/platform.c
build/amiga/libamposix.a: $(AMIGA_OBJECTS)
	$(AMIGA_AR) rcs $@ $^
build/amiga/amposix-qualification: qualification/amiga.c build/amiga/libamposix.a
	$(AMIGA_CC) $(AMIGA_CPPFLAGS) $(AMIGA_CFLAGS) -o $@ qualification/amiga.c build/amiga/libamposix.a
amiga-smoke: build/amiga/libamposix.a
amiga-qualification: build/amiga/amposix-qualification
build/amiga/payload: build/amiga/amposix-qualification qualification/amiga-runtime.json qualification/run-amiga-qualification
	mkdir -p $@
	cp build/amiga/amposix-qualification $@/
	cp qualification/amiga-runtime.json $@/
	cp qualification/run-amiga-qualification $@/
amiga-payload: build/amiga/payload

AMIGA_PROBES = build/amiga/probe-read-eclock.o build/amiga/probe-timer-device.o build/amiga/probe-datestamp.o build/amiga/probe-getaddrinfo.o build/amiga/probe-gethostbyname.o
build/amiga/probe-read-eclock.o: qualification/probes/read-eclock.c | build/amiga
	$(AMIGA_CC) $(AMIGA_CFLAGS) -c -o $@ $<
build/amiga/probe-timer-device.o: qualification/probes/timer-device.c | build/amiga
	$(AMIGA_CC) $(AMIGA_CFLAGS) -c -o $@ $<
build/amiga/probe-datestamp.o: qualification/probes/datestamp.c | build/amiga
	$(AMIGA_CC) $(AMIGA_CFLAGS) -c -o $@ $<
amiga-probes: $(AMIGA_PROBES)
build/amiga/probe-getaddrinfo.o: qualification/probes/getaddrinfo.c | build/amiga
	$(AMIGA_CC) $(AMIGA_CFLAGS) -Werror=implicit-function-declaration -c -o $@ $<
build/amiga/probe-gethostbyname.o: qualification/probes/gethostbyname.c | build/amiga
	$(AMIGA_CC) $(AMIGA_CFLAGS) -c -o $@ $<
