#include <stdio.h>

int main(void)
{
    int hour, minutes, hour1, minutes1;


    do {
        printf("Enter current time (hh:mm):");
        scanf("%d:%d", &hour, &minutes);



        if (hour < 0 || hour >= 24 || minutes < 0 || minutes >= 59) {
            puts("enter in correct format");

        }

    } while (hour < 0 || hour >= 24 || minutes < 0 || minutes >= 59);



    do {
        printf("How long do you want to sleep (h:mm):");
        scanf("%d:%d", &hour1, &minutes1);


        if (hour1 < 0 || hour1 >= 24 || minutes1 < 0 || minutes1 >= 59) {
            puts("enter in correct format");
        }
    } while (hour1 < 0 || hour1 >= 24 || minutes1 < 0 || minutes1 >= 59);



    minutes = minutes + minutes1;

    if (minutes >= 60) {
        minutes -= 60;
        hour += 1;
    }

    hour = hour + hour1;

    if (hour >= 24) {
        hour -= 24;

    }


    printf("If you go to bed now you must wake up at :%d:%d.\n", hour, minutes);

    return 0;


}