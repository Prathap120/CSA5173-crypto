#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_SIZE 10000
#define ALPHABET_SIZE 26

const double ENGLISH_FREQUENCY[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 
    1.974, 0.074
};

typedef struct {
    char letter;
    double frequency;
} LetterFrequency;

void calculate_frequency(const char *text, LetterFrequency freq[]) {
    int total_letters = 0, counts[ALPHABET_SIZE] = {0};
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = toupper(text[i]);
            counts[letter - 'A']++;
            total_letters++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i].frequency = (double)counts[i] / total_letters * 100.0;
    }
}

void sort_by_frequency(LetterFrequency freq[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (freq[j].frequency < freq[j + 1].frequency) {
                LetterFrequency temp = freq[j];
                freq[j] = freq[j + 1];
                freq[j + 1] = temp;
            }
        }
    }
}

void generate_plaintexts(const char *ciphertext, const LetterFrequency cipher_freq[], int num_plaintexts) {
    char mapping[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[cipher_freq[i].letter - 'A'] = 'A' + i;
    }
    for (int k = 0; k < num_plaintexts; k++) {
        printf("\nPlaintext #%d:\n", k + 1);
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            mapping[cipher_freq[i].letter - 'A'] = 'A' + ((i + k) % ALPHABET_SIZE);
        }
        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (isalpha(ciphertext[i])) {
                char letter = toupper(ciphertext[i]);
                char decoded = mapping[letter - 'A'];
                printf("%c", islower(ciphertext[i]) ? tolower(decoded) : decoded);
            } else {
                putchar(ciphertext[i]);
            }
        }
        printf("\n");
    }
}

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    int num_plaintexts;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    printf("Enter the number of possible plaintexts to generate: ");
    scanf("%d", &num_plaintexts);
    LetterFrequency cipher_freq[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        cipher_freq[i].letter = 'A' + i;
    }
    calculate_frequency(ciphertext, cipher_freq);
    sort_by_frequency(cipher_freq, ALPHABET_SIZE);
    LetterFrequency english_freq[ALPHABET_SIZE] = {0};
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        english_freq[i].letter = 'A' + i;
        english_freq[i].frequency = ENGLISH_FREQUENCY[i];
    }
    sort_by_frequency(english_freq, ALPHABET_SIZE);
    printf("\nAnalyzing and generating plaintexts...\n");
    generate_plaintexts(ciphertext, cipher_freq, num_plaintexts);
    return 0;
}
