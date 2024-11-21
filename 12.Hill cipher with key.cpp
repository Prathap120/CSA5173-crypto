#include <stdio.h>
#include <string.h>
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
void matrix_multiply(int key[2][2], int input[2], int output[2], int mod) {
    for (int i = 0; i < 2; i++) {
        output[i] = 0;
        for (int j = 0; j < 2; j++) {
            output[i] += key[i][j] * input[j];
        }
        output[i] %= mod;
    }
}
void encrypt(char *plaintext, int key[2][2], char *ciphertext) {
    int input[2], output[2];
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        input[0] = plaintext[i] - 'A';
        input[1] = plaintext[i + 1] - 'A';
        matrix_multiply(key, input, output, 26);
        ciphertext[i] = output[0] + 'A';
        ciphertext[i + 1] = output[1] + 'A';
    }
    ciphertext[len] = '\0';
}
void decrypt(char *ciphertext, int key[2][2], char *plaintext) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;
    int det_inv = mod_inverse(det, 26);
    int inv_key[2][2];
    inv_key[0][0] = key[1][1] * det_inv % 26;
    inv_key[0][1] = -key[0][1] * det_inv % 26;
    inv_key[1][0] = -key[1][0] * det_inv % 26;
    inv_key[1][1] = key[0][0] * det_inv % 26;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inv_key[i][j] < 0) inv_key[i][j] += 26;
        }
    }
    int input[2], output[2];
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        input[0] = ciphertext[i] - 'A';
        input[1] = ciphertext[i + 1] - 'A';
        matrix_multiply(inv_key, input, output, 26);
        plaintext[i] = output[0] + 'A';
        plaintext[i + 1] = output[1] + 'A';
    }
    plaintext[len] = '\0';
}
int main() {
    char plaintext[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    char ciphertext[100], decryptedtext[100];
    int key[2][2] = {{6, 5}, {7, 8}};

    if (strlen(plaintext) % 2 != 0) {
        strcat(plaintext, "X");
    }
    printf("Original Plaintext: %s\n", plaintext);

    encrypt(plaintext, key, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, key, decryptedtext);
    printf("Decrypted Plaintext: %s\n", decryptedtext);
    return 0;
}
