# Motor Control

This exercise will show you how easy it is to write software for
micro-controllers.


Using tests which describe the desired behavior of the application,
and simple abstractions which hide the implementation details, we will
build a working application for an Atmel328p microprocessor, otherwise
known as an Arduino Nano.

## Requirements

  - C tool suite for your platform. On OSX this will mean installing
    X-code AVR toolchain.  This includes avr-gcc, avr-g++, avr-gnu-ar
  - The Arduino software suite.  You can download it from
    http://www.arduino.cc
  - A text editor.  Atom or VS-Code are recommended, but any code
    editor which you are comfortable with will work.

## Application Goals

The application hardware consists of a motor attached to a pulley with
a string.  The motor is capable of being run up or down.  There is
also a limit switch set up so that when something is raised to the top
via the pulley, the limit switch with be closed.

When the application is started, the string is extended to it's
maximum desired extent.  The motor will pull the string up, and keep
track of how many cycles were required to raise the string.

When the limit switch is closed, the motor will stop raising the
string and start running the string down.  It will count the number of
cycles until it is at its fullest extent.  It will then it will return
to the raising cycle.

## The Exercise

  - Extract the archive containing this file to someplace on your computer.
  - Open a command shell that folder.
  - Change to the test folder (i.e.: `cd test`)

### The Tests

This code is written using a process called Test Driven Development.
That means I write a test which describes a state I wish to be true.
I run the test to ensure that it fails.  I then write just enough code
to make the test pass.  I run the test again and see that it now
passes.

This archive contains the full suite of tests which I wrote to test
drive this application.  When all of the tests pass, you will have a
minimally working version of the program.

The files `test/test_controller.c` and `test/test_state_transition.c`
contains all of the tests which are used to ensure that the program works as
desired.  The tests have a consistent format:

    TEST(Controller, setup_byDefault_initializesMotorState)

Inside the parens, the first word, Controller, refers to the test
suite to which this belongs.  The Controller test suite tests the
functions of the file `src/controller.c`.

The second 'word' is broken into three parts, separated by the '_' character.  

  - The first part is the function being tested.  In this example, the
    test is for the `setup()` function in `controller.c`.
  - The second part is the condition under which this test applies.
    In this example, "by default" means that there are no conditions,
    and therefor no if statements, around the part being tested.
  - The third part is what must be true for this test to pass.  In
    this case we must initialize the `MOTOR_STATE` object (which is
    defined in `controller.h`)

You can use the actual content of the tests as a guide to determine
what must be done to make the test pass.  The tests are:

    TEST_ASSERT_EQUAL(0, MOTOR_STATE.position);
    TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
    TEST_ASSERT_EQUAL(UNSET, MOTOR_STATE.max_position);

In the `setup()` of `controller.c` this means you should have the
following code:

    MOTOR_STATE.direction = UP;
    MOTOR_STATE.position = 0;
    MOTOR_STATE.max_position = UNSET;

### Reading The Tests

In many of the tests you will see lines which begin with `mock_`.
This is where I have used test doubles, i.e. functions or objects that
stand in for the real functions or objects.  I do this for a couple of
reasons.

  - The function relies on hardware which only exists on the Arduino
    microprocessor, and I obviously don't have that on my development
    computer.

  - I want to see if a function is called, but for my test I don't
    care about what happens in that function.  Assuming that my
    function has been tested to guarantee that it has the proper
    behavior, this makes what could be a complicated test very simple.

When you are trying to write code to make a test pass, there are three
general cases you need to know for test doubles:

  `mock_was_called`: Returns true if the function in parens was called, 
                   false if it was not.

  `mock_was_called_with`: Returns the value that the listed function
                   was called with.  Returns -1 if the function was
                   not called.

  `mock_called_inorder`: Returns true if the listed functions were
                   called in the order they are listed.  False if the
                   functions were called in a different order or were
		   not called at all.

There are also functions which are part of the test double framework
that control how other functions behave:

  `timer_value_will_return`: Controls the values with `timer_value()`
  			     will return in tests.  The first argument
  			     is the number of values which have been
  			     specified.  Every call to `timer_value()`
  			     in the source code will get the next
  			     value off the list.  If the timer values
  			     are not specified or `timer_value()` is
  			     called more times than there are list
  			     items, `timer_value()` will return 0.

 `switch_state_will_return`: The value passed will be the value
 			     returned for every call to
 			     `switch_state()`. 

### Running Tests

To run tests you need to be at the command line, in the `test/`
directory.  This is the directory named `test` within the collection
of files that you unzipped for checked out of source control for this
exercise.  

At the command line, run tests:

    make

This will make and run the test suite.  You should see a list of
errors reported.


### Skipping to the End

If you run short on time, or just want to see the device work, the
folder `answers/` contains my own solution to make all of the tests
pass.  You can copy the files from that folder into `src/`.

## Running on Hardware

To build for hardware, you must edit `src/Makefile`. The variable
`ARDUINO_BASE` must be modified to set the value to the location of
the file `Arduino.h`.  The easiest way to find this is with the
following command:

    find /Applications -name "Arduino.h"

To build your software you will need to be in the `src/` folder at the
command line.

    make clean
    make
    sudo make upload

This will cause any stray files from earlier builds to be removed, a
new version of the motorcontroller software to be built, and the
software to be uploaded to the Arduino which you have attached via USB
cable.

Take particular note of the third command, which begins with `sudo`.
This is a special command which indicates that subsequent commands
should be run as an administrator.  If your upload fails but you have
your Arduino connected to USB (the power light will come on), check
for the `sudo` at the start of your upload command.
