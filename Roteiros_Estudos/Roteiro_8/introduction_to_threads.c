#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* routine(void* args) {
    char* str = (char*) args;

    printf("%s\n", str);

    char* return_str = (char*) malloc((strlen("hello from ") + strlen(str) + 1)*sizeof(char));
    sprintf(return_str, "hello from %s", str); 

    return return_str;
}

int main(int argc, char** argv) {
    pthread_t t1, t2;
    
    int error_code = 0;
    if( (error_code = pthread_create(&t1, NULL, routine, "thread 1")) != 0 )
        exit(error_code);
        
    if( (error_code = pthread_create(&t2, NULL, routine, "thread 2")) != 0 )
        exit(error_code);
    
    char* return1 = NULL;
    char* return2 = NULL;
    pthread_join(t1, (void**) &return1);
    pthread_join(t2, (void**) &return2);

    printf("%s\n", return1);
    printf("%s\n", return2);

    return 0;
}
