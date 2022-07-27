#include<stdio.h>
#include<string.h>


int main()
{
    char message[100], ch;
    int i, key;
    printf("Enter a message to encrypt: ");
    fgets (message,100,stdin);
    for(i=0;i<=strlen(message);i++){
        if(message[i]>=97&&message[i]<=122)
            message[i]=message[i]-32;
    }


    printf("Enter amount of shift: ");
    scanf("%d", &key);
    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];

        if(ch >= 'A' && ch <= 'Z'){
            ch = ch + key;
            if(ch > 'Z'){
                ch = ch - 'Z' + 'A' - 1;
            }

            message[i] = ch;
        }

    }
    printf("Encrypted message: %s", message);

    for(i = 0; message[i] != '\0'; ++i){
        ch = message[i];
        if(ch >= 'A' && ch <= 'Z'){
            ch = ch - key;
            if(ch < 'A'){
                ch = ch + 'Z' - 'A' + 1;
            }
            message[i] = ch;
            }

        }
    printf(" Decrypted message: %s\n", message);
    return 0;
}