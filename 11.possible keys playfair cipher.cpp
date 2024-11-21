#include <stdio.h>
#include <math.h>
double log2_factorial(int n) {
    double log2_fact = 0.0;
    for (int i = 1; i <= n; i++) {
        log2_fact += log2(i);
    }
    return log2_fact;
}
int main() {
    int n = 25;
    int grid_dim = 5;
    double log2_total_keys = log2_factorial(n);
    double log2_row_perm = log2_factorial(grid_dim);
    double log2_unique_keys = log2_total_keys - 2 * log2_row_perm - log2(2);
    printf("Total possible keys: 2^%.2f\n", log2_total_keys);
    printf("Effectively unique keys: 2^%.2f\n", log2_unique_keys);
    return 0;
}

