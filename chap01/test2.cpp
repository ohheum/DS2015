#include <stdio.h>
#include <string.h>


struct T {
    int data[10];
    int cnt;
};


int main(void) {
    struct T a;
    for (int i=0; i<10; i++)
        a.data[i] = i+1;

    struct T b;
    b= a;
    a.data[0] = 10;
    for (int i=0; i<10; i++)
        printf("%d ", b.data[i]);
    printf("\n");

    return 0;
}