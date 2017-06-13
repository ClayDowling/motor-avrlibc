# Motor Controller with AVR libc

This is test driven application for controlling a motor using avr-libc.  While
avr-libc is harder to use to control a motor than Wiring (Arduino) or similar
libraries, it isn't wildly difficult if you read the documentation and any of
the excellent tutorials out there.

Most importantly, programs written with avr-libc make it really easy to test
drive the code and mock hardware interfaces, so I can define and test behavior
easily without having to go through a constant but slow build->deploy->run cycle.

## Operation

The motor controller assumes a pully mechanism which starts with the rope at its
furthest extent from the pully.

The motor is run in the Up direction, and the number of cycles consumed is
recorded, until the limit switch is closed.

When the switch is closed, the motor reverses direction and continues until
the same number of cycles have expired as were used to pull the rope up.  In this
manner the mechanism should continue lowering and raising the pulley for roughly
the same distance each time.  Some variation is expected because the system does
not contain any encoders, or use stepper motors which can closely control the
number of revolutions.
