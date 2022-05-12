test: testrun clean

tests: tests.c tuple.h 
	gcc -o test tests.c tuple.h tuple.c canvas.h canvas.c -std=c99 -lm

testrun: tests 
	./test
debug:
	gcc -o test tests.c tuple.h tuple.c canvas.h canvas.c -std=c99 -lm  -g
	@echo "run gdb ./test to debug"

clean:
	rm ./test
