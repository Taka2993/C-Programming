#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


#include <time.h>
char* PasswordGenerator(char* pw, size_t size, const char* word)
{
    size_t wordsize = strlen(word);
    size_t pos = 0;


    for(size_t i = 0; i<size; i++) {
        if(rand()%2) pw[i] = 'a';
        else pw[i] = 'A';
        pw[i] += rand()%26;
    }


    pos = rand() % (size - wordsize);
    memcpy(&pw[pos], word,wordsize);

    return pw;
}


int main(void)
{
    char* words[] = {
            "test",   "sample",    "temp",    "word",  "C",
            "c++" , "C#" , "python" , "Java" , "PHP"
    };

    srand((unsigned int)time(NULL));

    char pw[13] = { 0 };


    for(int i = 0; i<3; i++) {
        PasswordGenerator(pw, 12, words[rand()%10]);
        printf("PW%d:%s\n",i+1, pw);
    }

    return 0;
}