#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "aes/include/aes_config.h"
#include "aes/include/aes_utils.h"
#include "aes/include/aes.h"

char hex[16] = "0123456789ABCDEF";
void printCharArr(u8* arr, int len, bool asChar) {
    printf("{ ");
    for (int i = 0; i < len; i++)
        printf("%c%c ", hex[arr[i] >> 4], hex[arr[i] & 0x0f]);
    printf("}\n");
}

int main() {
    printf("Hello, World!\n");

    char* txt = "sdfjklewjoivjiowoive";
    char* key = "fwefnwfwfwfew";
    char* cipher = NULL;

    aes_encrypt(txt, 32, key, 16, &cipher);

    puts("Plaintext: ");
    printCharArr(txt, 32, false);
    puts("Key: ");
    printCharArr(key, 16, false);
    puts("Cipher: ");
    printCharArr(cipher, 32, false);

    return 0;
}