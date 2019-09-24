all:
	gcc ./src/*.c -o kiwi -I include -L lib -l SDL2-2.0.0 && ./kiwi

clean:
	rm index.html index.js index.wasm kiwi
