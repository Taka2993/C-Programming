#include <stdio.h>
#include <string.h>

char A[100] ;
char B[100] = "stop";
char C[100] = "STOP";

void func();

int main (void) {

    do{
        printf("Enter a message: ");
        fgets(A, 100, stdin);
        func();
        printf ("\n message: %s\n\n", A);




    } while (strncmp(A,B,4)&&strncmp(A,C,4) != 0);


 return 0;
}


    void func() {

        char *a = A;

        while (*a) {
            if (*a == ' ')
                *a = '_';
            a++;
        }
    }
