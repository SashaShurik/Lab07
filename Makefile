all: clean prep compile run 

clean:
	rm -rf dist
prep: 
	mkdir dist
compile:
	gcc -g src/main.c -o dist/main.bin
	@doxygen
doxygen:
	doxygen Doxyfile
format:#TODO

tidy:#TODO

