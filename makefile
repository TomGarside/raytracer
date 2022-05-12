test: testrun clean

debug: testrun debug-gdb

tests: tests.c tuple.h 
	gcc -o test tests.c tuple.h tuple.c canvas.h canvas.c -std=c99 -lm -g 

testrun: tests 
	./test
debug-gdb:
	gdb ./test

clean:
	rm ./test
