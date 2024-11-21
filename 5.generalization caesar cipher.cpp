#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int is_valid_a(int a) {
    return gcd(a, 26) == 1;
}

char affine_encrypt(char p, int a, int b) {
    if (p >= 'A' && p <= 'Z') {
        return ((a * (p - 'A') + b) % 26) + 'A';
    } else if (p >= 'a' && p <= 'z') {
        return ((a * (p - 'a') + b) % 26) + 'a';
    }
    return p;
}

char affine_decrypt(char c, int a, int b) {
    int a_inv = 0;
    for (int i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1) {
            a_inv = i;
            break;
        }
    }
    if (c >= 'A' && c <= 'Z') {
        return (a_inv * ((c - 'A' - b + 26) % 26)) % 26 + 'A';
    } else if (c >= 'a' && c <= 'z') {
        return (a_inv * ((c - 'a' - b + 26) % 26)) % 26 + 'a';
    }
    return c;
}

int main() {
    int a, b;
    char plaintext[100], ciphertext[100];
    
    printf("Enter values for a and b: ");
    scanf("%d %d", &a, &b);

    if (!is_valid_a(a)) {
        printf("Invalid value of a. It must be coprime with 26.\n");
        return 1;
    }

    printf("Enter plaintext: ");
    scanf("%s", plaintext);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        ciphertext[i] = affine_encrypt(plaintext[i], a, b);
    }
    ciphertext[strlen(plaintext)] = '\0';

    printf("Ciphertext: %s\n", ciphertext);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        plaintext[i] = affine_decrypt(ciphertext[i], a, b);
    }
    plaintext[strlen(ciphertext)] = '\0';

    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

