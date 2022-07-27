#include <stdio.h>
#include <math.h>
int main(void){
    int  count=0,count1=0, i;
    float a[256];
    double ave=0.0;
    FILE *fp;


    if((fp = fopen("test.txt", "r")) == NULL){
        printf("file open error!!\n");
        return -1;
    }

    fscanf(fp, "%d", &count1);


    while(fscanf(fp, "%f", &a[count]) != EOF){
        count++;
    }

    if(count1 !=count ){
        printf("Error! Tried to read %d numbers, %d numbers were read. \n", count1, count);

    }
    fclose(fp);

    for(i=0; i<count; i++){
        ave += a[i];
    }
    ave /= count;



    printf("Average of %d numbers is: %.3f \n", count, ave);
    return 0;
}