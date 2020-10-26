#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *p = malloc(10 * sizeof(int));
    printf("Memory allocated\n");
    free(p);
    printf("First free\n");
    free(p);
    printf("Second free\n");
    return 0;
}