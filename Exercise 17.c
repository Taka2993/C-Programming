#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct {
    char make[32];
    char model[32];
    int  price;
    float emissions;
}CAR_DATA;

int main(void)
{
    char* path = "CAR_DATA.dat";
    FILE* fp;
    size_t filesize = 0;
    CAR_DATA data;
    int menuNo = 0;

    while(1) {

        printf("Menu ... \n ");
        printf("5.Show All Car Data\n ");
        printf("6.Add new Car Data\n ");
        printf("7.Quit Program\n ");
        printf("Input menu No >> ");
        scanf("%d", &menuNo);

        if(menuNo <5 || menuNo > 7) continue;

        if(menuNo == 5) {

            fp = fopen(path, "rb");
            if(fp == NULL) {
                printf("File Open Error!!! \n");
                return -1;
            }

            fseek(fp, 0, SEEK_END);
            filesize = ftell(fp);
            fseek(fp, 0, SEEK_SET);

            for(int i = 0; i < filesize / sizeof(CAR_DATA); i++) {
                fread(&data, sizeof(CAR_DATA), 1, fp);
                printf("\n--------------\n");
                printf("make     :%s\n", data.make);
                printf("model    :%s\n", data.model);
                printf("price    :%d\n", data.price);
                printf("emissions:%f\n", data.emissions);
                printf("\n");
            }
            fclose(fp);
        }
        if(menuNo == 6) {
            memset(&data, 0, sizeof(data));	//0??????

            printf("Input Car Data\n");
            printf("make ? >> ");
            scanf("%s", data.make);
            if(data.make[31] != 0) {
                printf("make length Error!!!");
                continue;
            }
            printf("model ? >> ");
            scanf("%s", data.model);
            if(data.model[31] != 0) {
                printf("model length Error!!!");
                continue;
            }

            printf("price ? >> ");
            scanf("%d", &data.price);
            if(data.price <  0) {
                printf("price data Error!!!");
                continue;
            }

            printf("emissions ? >> ");
            scanf("%f", &data.emissions);
            if(data.emissions <  0) {
                printf("emissions data Error!!!");
                continue;
            }


            fp = fopen(path, "ab");
            if(fp == NULL) {
                printf("File Open Error!!! \n");
                return -1;
            }

            fwrite(&data, sizeof(data), 1, fp);
            fclose(fp);
        }

        if(menuNo == 7) break;

    }


    return 0;
}