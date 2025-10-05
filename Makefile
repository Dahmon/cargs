CC = gcc
AR = ar

CFLAGS  = -Wall -Wextra
SRC     = src
BUILD   = bin
INCLUDE = include
PREFIX  = /usr/local

.PHONY: all example install uninstall clean

all: $(BUILD)/libcargs.a

$(BUILD):
	mkdir $(BUILD)

$(BUILD)/libcargs.a: $(BUILD)/cargs.o
	$(AR) rcs $@ $^

$(BUILD)/cargs.o: $(SRC)/cargs.c $(INCLUDE)/cargs.h | $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ src/cargs.c

example: $(BUILD)/example.o $(BUILD)/libcargs.a
	$(CC) $(CFLAGS) -o $(BUILD)/$@ $^

$(BUILD)/example.o: example/example.c include/cargs.h | $(BUILD)
	$(CC) $(CFLAGS) -c -o $@ example/example.c

install: $(BUILD)/libcargs.a $(INCLUDE)/cargs.h
	install -d $(PREFIX)/lib
	install $(BUILD)/libcargs.a $(PREFIX)/lib
	install -d $(PREFIX)/include/cargs
	install include/cargs.h $(PREFIX)/include/cargs

uninstall:
	rm $(PREFIX)/lib/libcargs.a
	rm -rf $(PREFIX)/include/cargs

clean:
	rm -rf $(BUILD)
