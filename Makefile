all: build
	./kiwi

build:
	gcc ./src/*.c -o kiwi -Iinclude -Llib -llua53 -lSDL2 -lSDL2_image -Wall -Wextra -Werror -g

tags:
	ctags --c-types=+p -R .

clean:
	rm index.html index.js index.wasm kiwi

.PHONY: all build tags clean
