all: c.c
	gcc -o pipe c.c

run: all
	./pipe

clean:
	rm pipe *~

debug: c.c
	gcc -o debug -g c.c
