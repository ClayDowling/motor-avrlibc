CFLAGS=-I../mock -I../src -I../unity -I../machine -std=c99 -g
LDFLAGS=-L../unity -lunity
VPATH=../mock:../src

CONTROLLER_OBJS=test_mock.o test_controller.o TestGroupRunner.o runAllTests.o
CONTROLLER_SUT=controller.o
CONTROLLER_MOCKS=mock_transition.o mock_timer.o mock_motor.o mock_switch.o mock.o

TRANSITION_OBJS=test_transition.o TestTransitionRunner.o runTransitionTests.o
TRANSITION_SUT=state_transition.o
TRANSITION_MOCKS=mock_motor.o mock_switch.o mock_timer.o mock.o

MOCKS=mock_motor.o mock_switch.o mock_timer.o mock.o

all: test_controller test_transition
	./test_controller
	./test_transition

test_controller: $(CONTROLLER_OBJS) $(CONTROLLER_SUT) $(CONTROLLER_MOCKS)
	gcc $^ -o $@ $(LDFLAGS)

test_transition: $(TRANSITION_OBJS) $(TRANSITION_SUT) $(TRANSITION_MOCKS)
	gcc $^ -o $@ $(LDFLAGS)

clean:
	rm -f *.o
	rm -f test_controller
	rm -f test_transition
