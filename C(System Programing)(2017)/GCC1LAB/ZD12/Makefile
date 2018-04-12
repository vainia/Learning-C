OBJ_FILES_TOLIB=lnk/initapi.o lnk/randapi.o
SRC_FILES=initapi.c randapi.c
LIBRAS=lib/librapi.so
MAIN_FILE=src/test.c

CFLAGS=-Wall -fPIC
LDFLAGS=-Wall

debug/test: $(MAIN_FILE) $(SRC_FILES) $(LIBRAS)
	mkdir -p debug
	gcc -o $@ $(MAIN_FILE) $(LDFLAGS)

$(LIBRAS):
	mkdir -p lib
	gcc -shared -o $@ $(OBJ_FILES_TOLIB)

$(SRC_FILES):
	mkdir -p lnk
	gcc $(CFLAGS) -c src/$@ -o lnk/$*.o

clean:
	rm -rf lib lnk debug
