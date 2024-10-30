#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int global = 0;
int init_global = 1;
int uninit_global;

void callMe(int n, void *offset)
{
    if (n > 5)
        return;
    int local = n;
    printf("&local: %p offset: %p\n", (void *)&local, offset);
    printf("Call %d local - prev local:         %lld\n", n, (char *)&local - (char *)offset);
    printf("Call %d init_global:   %llu\\n", n, (uintptr_t)&init_global);
    printf("Call %d uninit_global: %llu\\n\n", n, (uintptr_t)&uninit_global);

    callMe(n + 1, &local);
}

int main()
{
    int local = 0;
    printf("main local:         %llu\n", (uintptr_t)&local);
    printf("main global:        %llu\n", (uintptr_t)&global);
    printf("main init_global:   %p\n", (void *)&init_global);
    printf("main uninit_global: %p\n\n", (void *)&uninit_global);

    callMe(1, &local);

    int *arr = (int *)malloc(10 * sizeof(int));
    int *arr2 = (int *)malloc(10 * sizeof(int));
    int *arr3 = (int *)malloc(10 * sizeof(int));
    int *arr4 = (int *)malloc(10 * sizeof(int));
    int *arr5 = (int *)malloc(10 * sizeof(int));

    printf("arr: %p\n", (void *)arr);
    printf("arr2: %lld\n", (char *)arr2 - (char *)arr);
    printf("arr3: %lld\n", (char *)arr3 - (char *)arr2);
    printf("arr4: %lld\n", (char *)arr4 - (char *)arr3);
    printf("arr5: %lld\n", (char *)arr5 - (char *)arr4);


    free(arr);
    free(arr2);
    free(arr3);
    free(arr4);
    free(arr5);

    return 0;
}
