.PHONY: clean
.SUFFIXES: .c .o

PREFIX := /usr/local

CFLAGS :=
CFLAGS += -Wall -Wextra
CFLAGS += -std=gnu99 -pedantic -g
CLFAGS += -pipe

.c:
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

TARGETS :=
TARGETS += hosted

all: build install
build: $(TARGETS)
install:
	test -d $(PREFIX)/bin || mkdir $(PREFIX)/bin
	for target in $(TARGETS); do \
		install -m 0755 $$target /usr/bin; \
	done

clean:
	rm -f $(TARGETS)
