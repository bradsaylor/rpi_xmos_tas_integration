#taken from tutorial @ http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

IDIR =../include
CC=gcc
CFLAGS=-g -I$(IDIR)

ODIR=obj
LDIR=../lib

LIBS= -lwiringPi


_DEPS = i2c.h LED_functions.h rpi_xmos_tas_integration.h TAS_functions.h UI_functions.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = i2c.o LED_functions.o TAS_functions.o UI_functions.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

rpi_xmos_tas_integration: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	ctags -e -R .. -h .c.h

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
