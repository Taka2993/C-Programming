#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>




typedef enum { AVAILABLE , LENT_OUT,STATE_MAX } CAR_STATE;

typedef struct
{
    char maker[10];
    char model[10];
    int plateNo;
    int distanse;
    char category[10];
    CAR_STATE state;
}CAR_DATA;

#define MAX_CAR_SIZE 15




void print_car_data(const CAR_DATA *p , size_t size , const char * cate)
{
    int count = 0;
    for(size_t i = 0; i < size; i++) {
        if((strcmp(cate, "*") == 0) ||
           (strcmp(cate, p[i].category) == 0 && p[i].state == AVAILABLE)) {
            printf("MAKER:%10s | MODEL:%10s | CATE:%10s | STATE:%10s | PLATE_NO:%04d | DISTANSE:%8d \n",
                   p[i].maker,p[i].model,p[i].category,p[i].category == AVAILABLE ? "AVAILABLE" : "LENT_OUT" , p[i].plateNo, p[i].distanse );
            count++;
        }
    }

    if(count)  printf("%d data Printed\n\n", count);
    else printf("No Match Data....\n\n");
}


int change_state(CAR_DATA* p, size_t size, int plateNo, CAR_STATE state)
{
    int ret = 0;
    for(size_t i = 0; i < size; i++) {
        if(p[i].plateNo == plateNo) {
            if(p[i].state == state) ret = 2;
            else {
                ret = 1;
                p[i].state = state;
            }
            break;
        }
    }
    return ret;
}


int main(int argc ,char **argv)
{

    CAR_DATA data[MAX_CAR_SIZE] = {
            //maker      model    plate   dist    cate    state
            { "TOYOTA" , "CROWN" , 1 ,   10000 , "SEDAN"  , AVAILABLE },
            { "TOYOTA" , "C-HR"  , 2 ,   20000 , "SUV"    , AVAILABLE },
            { "TOYOTA" , "RAV4"  , 3 ,   30000 , "SUV"    , AVAILABLE },
            { "TOYOTA" , "86"    , 4 ,    5000 , "SPORTS" , AVAILABLE },
            { "MAZDA"  , "CX-8"  , 5 ,    2000 , "SUV"    , AVAILABLE },
            { "MAZDA"  , "MAZDA6", 6 ,    1000 , "SEDAN"  , AVAILABLE },
            { "MAZDA"  , "ROADSTAR", 7 ,100000 , "SPORTS" , AVAILABLE },
            { "NISSAN" , "SELENA", 8   , 50000 , "MINIVAN", AVAILABLE },
            { "NISSAN" , "XTRAIL", 9   , 30000 , "SUV"    , AVAILABLE },
            { "NISSAN" , "FUGA"  , 10  , 70000 , "SEDAN"  , AVAILABLE },
            { "NISSAN" , "GT-R"  , 11  ,120000 , "SPORTS" , AVAILABLE },
            { "HONDA " , "INSIGHT" , 12 ,4000  , "SEDAN"  , AVAILABLE },
            { "HONDA " , "N-VAN"   , 13 ,10000 , "MINIVAN", AVAILABLE },
            { "HONDA"  , "S660"   , 14  ,7000  , "SPORTS" , AVAILABLE },
            { "HONDA"  , "FREED"  , 15  ,80000 , "MINIVAN", AVAILABLE }
    };

    int ret = 0;
    int menu = 0;
    int no = 0;
    int state = 0;
    char cate[128] = { 0 };

    //UI
    while(1) {
        menu = 0;
        while(1) {
            printf("menu ---- \n");
            printf("  1 : Show All Car Data\n");
            printf("  2 : Search Available Car\n");
            printf("  3 : Set Car State\n");
            printf("  4 : Quit Program\n");
            printf("input menu no >>> ");

            ret = scanf("%d", &menu);
            while((fgetc(stdin))!='\n') {};
            if(ret != 1 || menu < 1 || menu > 4) {
                printf("Menu No Error. TryAgain\n\n");
                continue;
            }
            printf("\n");
            break;
        }

        if(menu == 4)  break;
        else if(menu == 1) {
            print_car_data(data, MAX_CAR_SIZE , "*");
        }
        else if(menu == 2) {
            printf("input car category >>> ");
            ret = scanf("%s", &cate);
            print_car_data(data, MAX_CAR_SIZE, cate);
        }
        else if(menu == 3) {
            while(1) {
                printf("input Car plateNo (1-15)>>> ");
                ret = scanf("%d", &no);
                while((fgetc(stdin))!='\n') {};
                if(no < 1 || no > 15) continue;
                break;
            }
            while(1) {
                printf("How do you change the state?\n 0:AVAILABLE 1:LENT_OUT >>> ");
                ret = scanf("%d", &state);
                while((fgetc(stdin))!='\n') {};
                if(state < 0 || state > 1) continue;
                break;
            }
            switch(change_state(data, MAX_CAR_SIZE, no, (state==0 ? AVAILABLE : LENT_OUT))) {
                case 0:   printf("No Such PlateNo....\n\n"); break;
                case 1:   printf("State Change Success \n\n"); break;
                case 2:   printf("No Change Needed\n\n"); break;
                default:break;
            }

        }
    }

    return 0;
}
