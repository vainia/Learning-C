SRC_FILES=initapi.c randapi.c test.c
OBJ_FILES=initapi.o randapi.o test.o

CFLAGS=-Wall

zad2:	$(OBJ_FILES)
	gcc -o $@ $(OBJ_FILES)

%.o:%.c
	gcc $(CFLAGS) -c $<

clean:
	rm *.o zad2
