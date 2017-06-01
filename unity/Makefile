LIBNAME=unity

SRC=$(wildcard *.c)
BASES=$(basename $(SRC))
OBJS=$(addsuffix .o, $(BASES))

lib$(LIBNAME).a: $(OBJS)
	ar -rs $@ $^

clean:
	rm -rf *.o
	rm -rf *.a
