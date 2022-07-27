#include <stdio.h>


int main()
{
    int number;
    int sum = 0;
    int count = 0;

    printf("Enter the numbers and enter 0 to stop ");
    scanf("%d", &number);

    while (number != 0)
    {
        if (number > 0) {
            sum += number;
            count++;
        }
        else {
            printf("Enter only positive numbers\n");
        }

        printf("Enter another number or 0 to stop: ");
        scanf("%d", &number);
    }
    printf("AVERAGE = %f", ((float)sum)/ count);
}
