#include <stdio.h>



int main()
{

    FILE *fp;
    int n;

    char str[256], filename[256];
    float point[10];

    printf("Enter the file name: \n");
    scanf("%s", filename);



    if ((fp = fopen(filename, "r")) == NULL) {
        printf("fopen failed\n");
        return 0;
    }

    printf("Name                                                                           Price\n");

    for (n=0; n<4; n++) {
        fscanf(fp, "%f ; %[^\n] ",  &point[n],str);
        printf("%-40s              %30.2f  \n", str,point[n]);
    }



    fclose(fp);

    return 0;
}