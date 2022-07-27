#include <stdio.h>
#include <string.h>
#include <ctype.h>

char A[100] ;
char B[100] = "stop";
char C[100] = "STOP";


void func();

int main (void) {

    do{
        printf("Enter a message: ");
        fgets(A,sizeof A,stdin);
        func();
        printf ("\n message: %s\n\n", A);




    } while (strncmp(A,B,4)&&strncmp(A,C,4) != 0);


    return 0;
}


void func() {
    char *p;


    for(p=A; *p; p++){
        *p = toupper(*p);
    }
}