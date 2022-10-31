#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <time.h>

#define troca(arr, i, j) { int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp; }

void imprime_array(int* arr, int sz) {
    for(int i = 0; i < sz; i++)
        printf("%d, ", arr[i]);
    putchar('\n');
}

void insertion_sort(int* arr, int sz) {
    for(int i = 1; i < sz; i++) {
        for(int j = i - 1; j >= 0; j--)
            if(arr[i] < arr[j]) {
                troca(arr, i, j);
                i--;
            }
    }
}

int compara(const void* p1, const void* p2) {
    return *((int*) p1) > *((int*) p2);
}

int main(int argc, char** argv) {
    int arr[] = {-1, 5, 0, 2, -2, 0, -4, 3, 6, 4};

    int pid = fork();

    if(pid < 0) {
        perror("Erro no fork()\n");
        exit(1);
    }
    else if(pid > 0) {
        clock_t c1, c2;
        float tmp;
        c1 = clock();
        insertion_sort(arr, 10);
        c2 = clock();
        tmp = (c2 - c1)*1000.0/CLOCKS_PER_SEC;
        printf("O tempo gasto pelo pai foi: %0.5f\n", tmp);
        imprime_array(arr, 10);
        printf("Sou o pai, matei meu filho!\n");
        kill(pid, SIGKILL);
    }
    else {
        clock_t c1, c2;
        float tmp;
        c1 = clock();
        qsort(arr, 10, sizeof(int), compara);
        c2 = clock();
        tmp = (c2 - c1)*1000.0/CLOCKS_PER_SEC;
        printf("O tempo gasto pelo filho foi: %0.5f\n", tmp);
        imprime_array(arr, 10);
        printf("Sou o filho, matei meu pai!\n");
        kill(getppid(), SIGKILL);
    }
    
    return 0;
}
