all:
	gcc *.c -o kiwi -I include -L lib -l SDL2-2.0.0

clean:
	rm index.html index.js index.wasm kiwi
