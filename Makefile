.PHONY: all build tags clean

all: build
	./kiwi dev

build: src/generated_usage.h
	gcc ./src/*.c ./src/commands/*.c -o kiwi -Iinclude -Llib -llua53 -lSDL2 -lSDL2_image -Wall -Wextra -Werror -g

tags:
	ctags --c-types=+p -R .

clean:
	rm index.html index.js index.wasm kiwi

src/generated_usage.h: usage.txt
	cat usage.txt | awk -v ORS='\\n' '1' | sed 's/^/const char USAGE[] = "/' | sed 's/$$/";/' > $@
