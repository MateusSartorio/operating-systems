#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

int busca_binaria_rec(int* array, int target, int lo, int hi) {
    if(lo > hi)
        return - 1;

    int mid = lo + (hi - lo)/2;

    if(target == array[mid])
        return mid;
    else if(target > array[mid])
        return busca_binaria_rec(array, target, mid + 1, hi);
    else
        return busca_binaria_rec(array, target, lo, mid - 1);

    return -1;
}

int busca_binaria(int* array, int size, int target) {
    return busca_binaria_rec(array, target, 0, size - 1);
}

int main(int argc, char** argv, char** envp) {
    for(int i = 0; i < argc; i++)
        printf("%s, ", argv[i]);
    printf("\n");

    // int i = 0;
    // while(envp[i])
    //     printf("%s\n", envp[i++]);

    


    int* array = alloca((argc - 1)*sizeof(int));
    for(int i = 0; i < (argc - 1); i++)
        array[i] = atoi(argv[i + 1]);

    int valor = 1;
    printf("indice de %d eh %d\n", valor, busca_binaria(array, sizeof(array), valor));

    return 0;
}