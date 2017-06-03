CFLAGS=-I../mock -I../src -I../unity -I../machine -std=c99 -g
LDFLAGS=-L../unity -lunity
VPATH=../mock:../src

SRC=$(wildcard *.c)
BASES=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASES))

UNIT_UNDER_TEST=controller.o
MOCKS=mock_motor.o mock_switch.o mock.o

all: test_controller
	./test_controller

test_controller: $(OBJS) $(UNIT_UNDER_TEST) $(MOCKS)
	gcc $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o
	rm -f test_controller
