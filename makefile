test: testrun clean

tests: tests.c tuple.h 
	gcc -o test tests.c tuple.h tuple.c canvas.h canvas.c -std=c99 -lm 

testrun: tests 
	./test
clean:
	rm ./test
