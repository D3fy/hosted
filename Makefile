.PHONY: clean
.SUFFIXES: .c .o

CFLAGS :=
CFLAGS += -Wall -Wextra
CFLAGS += -std=gnu99 -pedantic -g
CLFAGS += -pipe

.c:
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

TARGET :=
TARGET += hosted

all: $(TARGET)

clean:
	rm -f $(TARGET)
