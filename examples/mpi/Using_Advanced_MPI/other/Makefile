ALL: all-redirect

##### User configurable options #####

CC      = mpicc
FC      = mpifort
CFLAGS  =
FCFLAGS =
LIBS    = 

# Programs or objects
PROGRAMS =
OBJECTS  = dtype.o flatten.o flatten_fns.o
SOURCES  = dtype.c flatten.c flatten_fns.c

all-redirect: $(PROGRAMS) $(OBJECTS)

# Rules
.SUFFIXES:
.SUFFIXES: .c .f .f90 .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c
.f90.o:
	$(FC) $(FCFLAGS) -c $*.f90
.f.o:
	$(FC) $(FCFLAGS) -c $*.f
sources:
	@echo ${SOURCES}
clean:
	rm -f *.o *~ $(PROGRAMS)

.PHONY: clean all-redirect default sources
