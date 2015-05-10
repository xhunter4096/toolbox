
all:
	gcc -o file-perf file-perf.c -static
clean:
	rm -rf file-perf
