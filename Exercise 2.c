#include <stdio.h>

int main() {
    double h;
    int grossincome;
    double arr[12];
    int i;

    printf("Input gross income: ");
    scanf("%d", &grossincome);

    h = (grossincome/12.5);

    for(i=0; i<12; i++)
    {
        arr[i] = h;
    }

    arr[6] = h*2;

    for(i=0; i<12; i++)
    {
        printf("element[ %5d] = ", i );
        printf("%.4f \n", arr[i]);
    }

    printf("total           = %d", grossincome );

    return 0;
}


