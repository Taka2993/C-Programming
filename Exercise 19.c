#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>



#ifdef DEBUG
#define DEBUGMSG	printf
#else
#define DEBUGMSG(...)
#endif



int main(void)
{
    int number;
    for(int i = 0; i<5; i++) {
        DEBUGMSG("loop:%d", i);
        printf("input number >>> ");
        scanf("%d", &number);
    }
    return 0;
}