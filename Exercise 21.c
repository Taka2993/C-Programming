#include <stdio.h>

int main() {
    int count[256] = { 0 };
    char filename[120];
    FILE *f;
    int ch;

    printf("Enter file name\n");
    if (scanf("%119[^\n]", filename) != 1)
        return 1;

    f = fopen(filename, "rb");
    if (f == NULL) {
        fprintf(stderr, "cannot open %s\n", filename);
        return 1;
    }
    while ((ch = fgetc(f)) != EOF) {
        count[ch]++;
    }
    fclose(f);

    for (int n = 0; n < 10; n++) {
        int maxcount = 0;
        for (int i = 1; i < 256; i++) {
            if (count[i] > count[maxcount])
                maxcount = i;
        }

        if (count[maxcount] != 0) {
            printf("[%c] = %d times used\n", maxcount, count[maxcount]);
            count[maxcount] = 0;
        } else {
            break;
        }
    }
    return 0;
}