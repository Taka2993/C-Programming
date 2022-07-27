#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char key[] = ".";
    char* text;

    FILE* fp;
    fp = fopen("test.txt", "w");
    if (fp == NULL)

    {
        printf("test.txt not opened.\n");
        return 0;
    }

    printf("User enters: ");

    int counter = 0;
    while (1)
    {
        if(!counter)
            text = (char*) malloc(sizeof (char));
        else
            text = (char*) realloc(text, (counter + 1) * sizeof(char));

        scanf("%c", &text[counter]);

        if(text[counter] == '\n')
        {
            text[counter] = 0;
            if(!strcmp(key, text))
                break;
            fprintf(fp, "%ld: %s\n", counter, text);
            printf("User enters: ");
            counter = 0;
            free(text);
        }
        else
            counter++;
    }

    free((void*)text);
    fclose(fp);

    puts("Exit program");

    return 0;
}
