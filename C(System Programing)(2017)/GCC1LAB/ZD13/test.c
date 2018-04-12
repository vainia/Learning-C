#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
int main(int argc, char const *argv[]) {
/***************************************************************************/
          /* Проверяем кол-во параметров.
          Если чего не так выводим сообщение об ошибке и уходим. */
          if (argc<2) {
   	   fprintf(stderr,"Usage: %s (./lib/libso.so)\n",argv[0]);
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
          void (*fsys)(void) = dlsym(handle, "fsys");
			 void (*fusr)(void) = dlsym(handle, "fusr");
          /* Если чего не так выводим сообщение об ошибке и уходим. */
          if (fsys == NULL || fusr == NULL) {
   	   fprintf(stderr,"%s\n",dlerror());
   	   exit(3);
          }
          /* Выводим название загруженной библиотеки. */
          printf("Loaded library: %s \nLib output:\n",argv[1]);
/***************************************************************************/
			fsys();
			fusr();
/***************************************************************************/
			/* Закрываем библиотеку. */
			dlclose(handle);
/***************************************************************************/
			return 0;
}
