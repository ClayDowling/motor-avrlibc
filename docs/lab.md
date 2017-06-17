# Motor Control

This exercise will show you how easy it is to write software for micro-controllers.

Using tests which describe the desired behavior of the application, and simple abstractions which hide the implementation details, we will build a working application for an Atmel328p microprocessor, otherwise known as an Arduino Nano.

## Requirements

  - Hardware - See circuit diagram.
  - C tool suite for your platform.  On OSX this will mean installing X-code
  - AVR toolchain.  This includes avr-gcc, avr-g++, avr-gnu-ar
  - A text editor.  Atom or VS-Code are recommended, but any code editor which you are comfortable with will work.

## Application Goals

The application hardware consists of a motor attached to a pulley with a string.  The motor is capable of being run up or down.  There is also a limit switch set up so that when something is raised to the top via the pulley, the limit switch with be closed.

When the application is started, the string is extended to it's maximum desired extent.  The motor will pull the string up, and keep track of how many cycles were required to raise the string.

When the limit switch is closed, the motor will stop raising the string and start running the string down.  It will count the number of cycles until it is at its fullest extent.  It will then it will return to the raising cycle.

## The Exercise

  - Extract the archive containing this file to someplace on your computer.
  - Open a command shell that folder.
  - Change to the test folder (i.e.: `cd test`)

This archive contains the full suite of tests which I wrote to test drive this application.  When all of the tests pass, you will have a minimally working version of the program.

The file `test/test_controller.c` contains all of the tests which are used to ensure that the program works as desired.  The tests have a consistent format:

    TEST(Controller, setup_byDefault_initializesMotorState)

Inside the parens, the first word, Controller, refers to the test suite to which this belongs.  The Controller test suite tests the functions of the file `src/controller.c`.

The second 'word' is broken into three parts, separated by the '_' character.  
  - The first part is the function being tested.  In this example, the test is for the `setup()` function in `controller.c`.
  - The second part is the condition under which this test applies.  In this example, "by default" means that there are no conditions, and therefor no if statements, around the part being tested.
  - The third part is what must be true for this test to pass.  In this case we must initialize the `MOTOR_STATE` object (which is defined in `controller.h`)

You can use the actual content of the tests as a guide to determine what must be done to make the test pass.  The tests are:

    TEST_ASSERT_EQUAL(0, MOTOR_STATE.position);
    TEST_ASSERT_EQUAL(UP, MOTOR_STATE.direction);
    TEST_ASSERT_EQUAL(UNSET, MOTOR_STATE.max_position);

In the `setup()` of `controller.c` this means you should have the following code:

    MOTOR_STATE.direction = UP;
    MOTOR_STATE.position = 0;
    MOTOR_STATE.max_position = UNSET;
