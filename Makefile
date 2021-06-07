salida_out = lab2
	
salida_headers = funciones.h
salida_source = $(salida_headers:.h=.c) lab2.c
salida_objects = $(salida_source:.c=.o)

CC     = gcc
CFLAGS = -Wall -lm

depends = .depends


$(salida_out) : $(salida_objects)
	$(CC) $(CFLAGS) -o $@ $^ -lm

$(objetcs) :
	$(CC) $(CFLAGS) -c -o $@ $*.c

$(depends) : $(salida_source) $(salida_headers)
	@$(CC) -MM $(salida_source) > $@

clean :
	$(RM) $(salida_out) $(salida_objects) $(zipfile)
.PHONY : build zip clean

sinclude : $(depends)