# Motor Controller Spike

This is spike code for an Arduino controlled motor.

The plan is to build the final object with avr-libc, rather than Wiring or
another microcontroller library.  While libraries are great, they cary a major
performance overhead, and the libraries are a major nuisance when test
driving your code.  Since the point of this spike is to work out a valid
test driving strategy, ease of testing is a major point in my decisions.
