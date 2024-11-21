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

int determinant_mod26(int matrix[2][2]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (det < 0) det += 26;
    return det;
}

void inverse_matrix_mod26(int matrix[2][2], int inverse[2][2]) {
    int det = determinant_mod26(matrix);
    int det_inv = mod_inverse(det, 26);

    inverse[0][0] = matrix[1][1] * det_inv % 26;
    inverse[0][1] = -matrix[0][1] * det_inv % 26;
    inverse[1][0] = -matrix[1][0] * det_inv % 26;
    inverse[1][1] = matrix[0][0] * det_inv % 26;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (inverse[i][j] < 0) inverse[i][j] += 26;
        }
    }
}

void matrix_multiply_mod26(int a[2][2], int b[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
            result[i][j] %= 26;
        }
    }
}

void solve_key_matrix(int plaintext[2][2], int ciphertext[2][2], int key[2][2]) {
    int plaintext_inverse[2][2];
    inverse_matrix_mod26(plaintext, plaintext_inverse);
    matrix_multiply_mod26(ciphertext, plaintext_inverse, key);
}

int main() {
    int plaintext[2][2] = {
        {19, 7},
        {4, 11}
    };

    int ciphertext[2][2] = {
        {15, 0},
        {8, 19}
    };

    int key[2][2];
    solve_key_matrix(plaintext, ciphertext, key);

    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    int verification[2][2];
    matrix_multiply_mod26(key, plaintext, verification);

    printf("\nVerification (Ciphertext):\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", verification[i][j]);
        }
        printf("\n");
    }

    return 0;
}
