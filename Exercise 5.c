
#include <stdio.h>

int main(void){

    int i, j, k, term;

    int a[1][3], b[3][3], c[1][3];

    printf("\n3 by 1 matrix\n");
    for(i=0;i<1;++i){
        for(j=0;j<3;++j){
            printf("A[%d][%d] = ", i+1, j+1);
            scanf("%d", &a[i][j]);
        }
    }

    printf("\n3 by 3 matrix\n");
    for(i=0;i<3;++i){
        for(j=0;j<3;++j){
            printf("B[%d][%d] = ", i+1, j+1);
            scanf("%d", &b[i][j]);
        }
    }
    printf("\n 3 by 1 matrix\n ");
    for(i=0;i<1;++i){
        for(j=0;j<3;++j) {
            printf("{%d }", a[i][j]);
            ;
        }
    }
    printf("\n 3 by 3 matrix\n ");
    for(i=0;i<3;++i){
        for(j=0;j<3;++j){
            printf("{%d }", b[i][j]);
        }
        printf("\n ");

    }

    for(i=0;i<1;++i){
        for(j=0;j<3;++j){
            c[i][j] = a[i][j] * b[i][j];

            for(i=0;i<1;i++){
                for(j=0;j<3;j++){
                    term = 0;
                    for(k=0;k<3;k++)
                        term = term + a[i][k]*b[k][j];
                    c[i][j] = term;
                }
            }

        }
    }


    printf("\n Result \n");
    for(i=0;i<1;++i){
        for(j=0;j<3;++j){
            printf("{%d }",c[i][j]);
        }
    }



    return 0;
}
