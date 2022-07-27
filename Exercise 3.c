#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>




float getAverage(const int* score, size_t size);

float getAverage(const int* score, size_t size)
{
    float sum = 0;
    for(size_t i = 0; i<size; i++)
    {
        sum += score[i];
    }
    return sum/size;
}

#define MAX_STUDENT_NUMBER 10
#define MAX_SCORE_VAL 5
#define STUDENT_ID_OFFSET 45000


int main(int argc ,char **argv)
{
    int score[MAX_STUDENT_NUMBER] = { 0 };
    int num = 0;
    int size = 0;
    int ret;

    while(1) {
        printf("input student Num (1-%d) >>> ", MAX_STUDENT_NUMBER);
        ret  = scanf("%d", &num);
        while((fgetc(stdin))!='\n') {};
        if(ret != 1 || num < 0 || num > MAX_STUDENT_NUMBER) {
            printf("student size error!\n");
        }
        else {
            break;
        }
    }

    size = num;
    num = 0;

    while(1) {
        if(num >= size) break;
        while(1) {
            printf("input [%d]'s score (0-5)>>> ", STUDENT_ID_OFFSET + num);
            ret = scanf("%d", &score[num]);
            while((fgetc(stdin))!='\n') {};
            if(ret != 1 || score[num] < 0 || score[num] > MAX_SCORE_VAL) {
                printf("score data error!\n");
                continue;
            }
            break;
        }
        num++;
    }

    printf("Score Average is %.2f \n", getAverage(score, size));
    return 0;
}
