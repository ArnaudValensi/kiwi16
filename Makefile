all:
	gcc ./src/*.c -o kiwi -Iinclude -Llib -llua53 -lSDL2 -lSDL2_image -g  && ./kiwi

clean:
	rm index.html index.js index.wasm kiwi
