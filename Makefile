CFLAGS += -Wall -Wextra -g
LDLIBS = -lcurses
INCLIBS = -Iinc
SH = /bin/sh

SRC_DIR = src
BUILD_DIR = out

PROJECT = miller_rabin

include res/help.mk

.PHONY: all clean help run
.SUFFIXES:
.DEFAULT: all

run: all
	$(SH) ./$(OUT)

help:; @ eval "$$usage"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	gcc $(CFLAGS) $(INCLIBS) -c $< -o $@

CFILES = $(wildcard $(SRC_DIR)/*.c)
OUT = $(PROJECT)
OBJS = $(CFILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(OUT)

$(OUT): $(OBJS)
	gcc -o $(OUT) $(OBJS)

clean:
	rm -rf $(BUILD_DIR)
