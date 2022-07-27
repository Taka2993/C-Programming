#include <stdio.h>
#include <stdlib.h>


int main(void)
{
    char path[1024] = {0};
    FILE* fp;
    size_t filesize = 0;
    size_t deleteOffset = 0;
    size_t deleteSize = 0;
    unsigned char* data;

    printf("Input File Path >> ");
    scanf("%s", path);

    fp = fopen(path, "rb");
    if(fp == NULL) {
        printf("File Open Error!!! \n");
        return -1;
    }


    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    printf("File Size is %lu \n" , filesize);

    printf("Input Delete Data offset >> ");
    scanf("%lu", &deleteOffset);
    if(deleteOffset > filesize) {
        printf("Delete offset value Error!!! \n");
        fclose(fp);
        return -1;
    }
    printf("Input Delete Data Size >> ");
    scanf("%lu", &deleteSize);
    if(deleteOffset+deleteSize > filesize) {
        printf("Delete data size Error!!! \n");
        fclose(fp);
        return -1;
    }


    data = malloc(filesize+1);
    if(data == NULL) {
        printf("Memory Allocation Error!!! \n");
        fclose(fp);
        return -1;
    }

    fseek(fp, 0, SEEK_SET);
    for(size_t i=0; i<filesize; i++) {
        data[i] = fgetc(fp);
    }
    data[filesize] = 0;
    fclose(fp);


    fp = fopen(path, "wb");
    if(fp == NULL) {
        printf("File Open Error!!! \n");
        return -1;
    }


    fwrite(data, 1, deleteOffset, fp);

    size_t pos = deleteOffset + deleteSize;
    fwrite(&data[pos], 1, filesize - pos, fp);

    free(data);
    fclose(fp);

    return 0;
}