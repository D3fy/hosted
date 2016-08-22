.PHONY: clean
.SUFFIXES: .c .o

PACKAGE := hosted
VERSION := 1.0.0
PREFIX  := /usr/local

CFLAGS :=
CFLAGS += -Wall -Wextra
CFLAGS += -std=gnu99 -pedantic -g
CLFAGS += -pipe

.c:
	$(CC) $(CFLAGS) $(LIBS) -o src/$@ $<

TARGETS :=
TARGETS += hosted

all: build install
build: $(TARGETS)
install:
	test -d $(DESTDIR)/$(PREFIX)/bin || mkdir -p $(DESTDIR)/$(PREFIX)/bin
	for target in $(TARGETS); do \
		install -m 0755 $$target $(DESTDIR)/$(PREFIX)/bin; \
	done

dist:
	rm -f $(PACKAGE)-$(VERSION).tar.gz
	mkdir -p $(PACKAGE)-$(VERSION)
	cp -a *.c $(PACKAGE)-$(VERSION)/
	cp -a Makefile $(PACKAGE)-$(VERSION)/Makefile
	tar -czf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)/
	rm -r $(PACKAGE)-$(VERSION)

rpm:
	$(call dist)
	cp $(PACKAGE)-$(VERSION).tar.gz ~/rpmbuild/SOURCES
	cp rpm.spec.in rpm.spec
	sed -i -e "s/@VERSION@/$(VERSION)/g" \
		-e "s/@PACKAGE@/$(PACKAGE)/g" rpm.spec
	rpmbuild -ba rpm.spec
	$(call clean)

clean:
	rm -f $(TARGETS)
	rm -f rpm.spec
