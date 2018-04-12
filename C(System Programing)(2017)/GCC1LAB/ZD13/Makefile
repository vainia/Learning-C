SRC_FILES=system.c users.c test.c
OBJ_FILES_TOLIB=system.o users.o
MAIN_FILE=test.o

CFLAGS=-Wall -fPIC
LDFLAGS=-Wall -ldl -o

test: $(MAIN_FILE) libso.so
	gcc $(LDFLAGS) $@ $(MAIN_FILE)

libso.so: $(OBJ_FILES_TOLIB)
	mkdir -p lib
	gcc -shared -o lib/$@ $(OBJ_FILES_TOLIB)

%.o:%.c
	gcc $(CFLAGS) -c $<

clean:
	rm -rf lib *.o test
