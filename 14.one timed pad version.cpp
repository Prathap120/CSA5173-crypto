#include <stdio.h>
#include <string.h>

void encrypt(char *plaintext, int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

void decrypt(char *ciphertext, int *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}

void find_key(char *ciphertext, char *plaintext, int *key) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            key[i] = (ciphertext[i] - plaintext[i] + 26) % 26;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            key[i] = (ciphertext[i] - plaintext[i] + 26) % 26;
        } else {
            key[i] = 0;
        }
    }
}

int main() {
    char plaintext[] = "send more money";
    char ciphertext[100];
    char decrypted_text[100];
    char target_plaintext[] = "cash not needed";
    int key[] = {9, 0, 17, 23, 15, 21, 14, 11, 11, 2, 8, 9, 7, 0, 0}; // Random key
    int recovered_key[100];
    int len = strlen(plaintext);

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, key, decrypted_text);
    printf("Decrypted Text: %s\n", decrypted_text);

    find_key(ciphertext, target_plaintext, recovered_key);

    printf("Recovered Key: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", recovered_key[i]);
    }
    printf("\n");

    return 0;
}
