#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int roof(int, int, int);

void f(int *p1, int size) {

    int k = 100;
    size *= 2;
    size += 2;
    k++;
    if(size>20)
        k *= 20;
    else if(size<10)
        k *= 10;
    else
        k *= 30;

    k = roof(k, size, size+k);

    size = size%k;

    int *p2 = malloc(size);
    int *p = memcpy(p2, p1, size);

    p2[0] = 0;

    printf("%d %d", p1[0], p2[0]);
}

int main()
{
    int size = 1024;
    int *p1 = malloc(size);

    f(p1, size);

    return 0;
}