CC      := gcc
CFLAGS  := -std=c17 -Wall -Wextra -Wpedantic -D_POSIX_C_SOURCE=200809L -Iinclude
AR      := ar
ARFLAGS := rcs

BUILDDIR := build
OBJDIR   := $(BUILDDIR)/obj

SRC := $(wildcard src/*.c)
OBJ := $(SRC:src/%.c=$(OBJDIR)/%.o)
LIB := $(BUILDDIR)/libaoc.a

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJ) | $(BUILDDIR)
	$(AR) $(ARFLAGS) $@ $^

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# create build/
$(BUILDDIR):
	mkdir -p $@

# create build/obj/
$(OBJDIR):
	mkdir -p $@

clean:
	rm -f $(OBJ) $(LIB)
