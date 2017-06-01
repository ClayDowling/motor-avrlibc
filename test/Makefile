CFLAGS=-I../mock -I../src -I../unity -std=c99
LDFLAGS=-L../unity -lunity
VPATH=../mock:../src

test_controller: test_controller.o controller.o motor.o switch.o
	gcc $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o
	rm -f test_controller
