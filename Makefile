# http://nuclear.mutantstargoat.com/articles/make/
# https://spin.atomicobject.com/2016/08/26/makefile-c-projects/

TARGET_EXEC = kiwi

BUILD_DIR = ./build
SRC_DIRS = ./src

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC = gcc
CFLAGS = $(INC_FLAGS) -Wall -Wextra -Werror -g
LDFLAGS = -Llib -llua53 -lSDL2 -lSDL2_image

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c src/generated_usage.h
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

src/generated_usage.h: usage.txt
	cat usage.txt | awk -v ORS='\\n' '1' | sed 's/^/const char USAGE[] = "/' | sed 's/$$/";/' > $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)

.PHONY: tags
tags:
	ctags --c-types=+p -R .

-include $(DEPS)

MKDIR_P ?= mkdir -p
