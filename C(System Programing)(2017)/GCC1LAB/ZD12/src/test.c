#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#define ITERATIONS  1000000L

int main(int argc,char *argv[])
{
/***************************************************************************/
          /* Проверяем кол-во параметров.
          Если чего не так выводим сообщение об ошибке и уходим. */
          if (argc<2) {
   	   fprintf(stderr,"Usage: %s [shared library name](in that case: ./lib/librapi.so)\n",argv[0]);
              exit(1);
          }
          /* Пытаемся загрузить библиотеку. */
          printf("Try to load library %s\n",argv[1]);
          void * handle = dlopen(argv[1], RTLD_LAZY);
          /* Если чего не так выводим сообщение об ошибке и уходим. */
          if (handle == NULL) {
              fprintf(stderr,"%s",dlerror());
   	        exit(2);
          }
          printf("Ok! Loaded!\n");
          /* Пытаемся загрузить функции библиотеки. */
          void (*initRand)(void) = dlsym(handle, "initRand");
          int (*getRand)(int) = dlsym(handle, "getRand");
          float (*getSRand)(void) = dlsym(handle, "getSRand");
          /* Если чего не так выводим сообщение об ошибке и уходим. */
          if (initRand == NULL || getRand == NULL || getSRand == NULL) {
   	   fprintf(stderr,"%s\n",dlerror());
   	   exit(3);
          }
          /* Выводим название загруженной библиотеки. */
          printf("Loaded library: %s \nLib output:\n",argv[1]);
/***************************************************************************/

        long i;
        long isum;
        float fsum;

        initRand();

        isum = 0L;
        for (i = 0; i < ITERATIONS; i++) {
                isum += getRand(10);
        }
        printf( "getRand() Average %d\n", (int)(isum / ITERATIONS) );

        fsum = 0.0;
        for (i = 0; i < ITERATIONS; i++) {
                fsum += getSRand();
        }

        printf( "getSRand() Average %f\n", (fsum / (float)ITERATIONS) );

/***************************************************************************/
        /* Закрываем библиотеку. */
        dlclose(handle);
/***************************************************************************/

        return 0;
}
