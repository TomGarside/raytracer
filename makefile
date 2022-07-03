test: testrun clean

tests: tests.c tuple.h 
	gcc -o test tests.c tuple.h tuple.c canvas.h canvas.c matrix.c matrix.h -std=c99 -lm

testrun: tests 
	./test
debug:
	gcc -o test tests.c tuple.h tuple.c canvas.h canvas.c matrix.c matrix.h -std=c99 -lm  -g
	@echo "run gdb ./test to debug"

clean:
	rm ./test 

projectile:
	gcc -o proj tuple.h tuple.c  projectile.h projectile.c  -std=c99 -lm 

projectile2:
	gcc -o proj* tuple.h tuple.c canvas.h canvas.c  projectile2.h projectile2.c  -std=c99 -lm 

