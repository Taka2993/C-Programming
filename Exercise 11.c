#include <stdio.h>


int main()
{

    FILE *fp;
    int n;
    int point[3];
    int i,j;
    int boxpoint;

    if ((fp = fopen("data.txt", "r")) == NULL) {
        printf("fopen failed\n");
        return 0;
    }


    printf(" The original text\n");

    for (n=0; n<3; n++) {
        fscanf(fp, "%d", &point[n]);
        printf(" %d \n", point[n]);
    }


    for(i = 0; i < 3; i++)
    {
        for(j = 0;j < 3; j++)
        {
            if(point[i] < point[j])
            {

                boxpoint = point[i];
                point[i] = point[j];
                point[j] = boxpoint;

            }}}


    printf(" Sorted\n");

    for(n=0;n<3;n++)
        printf(" %d \n", point[n]);

    fclose(fp);



    if ((fp = fopen("data.txt", "w")) == NULL) {
        printf("fopen failed\n");
        return 0;
    }


    for(n = 0; n < 3; n++){
        fprintf(fp, "%d \n", point[n]);
    }

    fclose(fp);



    return 0;
}