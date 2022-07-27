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
    char inpath[1024] = {0};
    char filedata[1024] = {0};
    FILE* fp , *fin;
    size_t filesize = 0;
    CAR_DATA data;
    int menuNo = 0;

    while(1) {

        printf("Menu ... \n ");
        printf("5.Show All Car Data\n ");
        printf("6.Add new Car Data\n ");
        printf("7.Add Car Data file\n ");
        printf("8.Quit Program\n ");
        printf("Input menu No >> ");
        scanf("%d", &menuNo);

        if(menuNo <5 || menuNo > 8) continue;

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
            memset(&data, 0, sizeof(data));

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


        if(menuNo == 7) {
            printf("Input File Path >> ");
            scanf("%s*c", inpath);

            fin = fopen(inpath, "r");
            if(fin == NULL) {
                printf("File Open Error!!! \n");
                return -1;
            }


            fseek(fin, 0, SEEK_END);
            filesize = ftell(fin);
            fseek(fin, 0, SEEK_SET);

            if(filesize > 1023) {
                printf("File Over Size(Max1023bytes) \n");
                fclose(fin);
                return -1;
            }

            char* p = filedata;
            while(filesize--) *p++ = fgetc(fin);
            fclose(fin);

            char* next, * q;
            char tmp[32];
            p = filedata;

            memset(&data, 0, sizeof(CAR_DATA));

            while(1) {
                p = strstr(p, "{");
                if(p== NULL) break;
                next = strstr(p, "}");
                if(next == NULL) {
                    printf("Data Error no \"}\"...\n");	break;
                }

                q = strstr(p, "\"model\":");
                if(q == NULL || q > next) { printf("Data Error no \"model:\"...\n");	break; }
                sscanf(q, "%s \"%[^\"]", tmp, data.model);

                q = strstr(p, "\"make\":");
                if(q == NULL || q > next) { printf("Data Error no \"make:\"...\n");	break; }
                sscanf(q, "%s \"%[^\"]", tmp, data.make);

                q = strstr(p, "\"price\":");
                if(q == NULL || q > next) { printf("Data Error no \"price:\"...\n");	break;	}
                sscanf(q, "%[^:]:%d", tmp, &data.price);

                q = strstr(p, "\"emissions\":");
                if(q == NULL || q > next) { printf("Data Error no \"emissions:\"...\n");	break;	}
                sscanf(q, "%[^:]:%f", tmp, &data.emissions);

                if(data.model[0] == 0) { printf("model data Error!!!");		break; }
                if(data.make[0] == 0) { printf("make data Error!!!");		break; }
                if(data.price <  0) {	printf("price data Error!!!");		break;	}
                if(data.emissions <  0) {		printf("emissions data Error!!!");	break;	}



                fp = fopen(path, "ab");
                if(fp == NULL) {
                    printf("File Open Error!!! \n");
                    fclose(fp);
                    break;
                }

                fwrite(&data, sizeof(data), 1, fp);
                fclose(fp);
                p = next;
            }

        }
        if(menuNo == 8) break;
    }


    return 0;
}