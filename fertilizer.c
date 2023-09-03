#include <stdio.h>
#include <stdlib.h>

void lstsq(int n, int m, float** a, float* b, float* x) {
    int i, j, k;
    float** ata;
    float* atb;
    
    // Allocate memory for matrices
    ata = (float**)malloc(m * sizeof(float*));
    for (i = 0; i < m; i++) {
        ata[i] = (float*)malloc(m * sizeof(float));
    }
    atb = (float*)malloc(m * sizeof(float));
    
    // Calculate ATA and ATB matrices
    for (i = 0; i < m; i++) {
        for (j = 0; j < m; j++) {
            ata[i][j] = 0.0;
            for (k = 0; k < n; k++) {
                ata[i][j] += a[k][i] * a[k][j];
            }
        }
        atb[i] = 0.0;
        for (k = 0; k < n; k++) {
            atb[i] += a[k][i] * b[k];
        }
    }
    
    // Gaussian elimination to solve the system of equations
    for (i = 0; i < m; i++) {
        for (j = i + 1; j < m; j++) {
            float ratio = ata[j][i] / ata[i][i];
            for (k = 0; k < m; k++) {
                ata[j][k] -= ratio * ata[i][k];
            }
            atb[j] -= ratio * atb[i];
        }
    }
    
    // Back substitution to find the solution
    for (i = m - 1; i >= 0; i--) {
        x[i] = atb[i] / ata[i][i];
        for (j = i - 1; j >= 0; j--) {
            atb[j] -= ata[j][i] * x[i];
        }
    }
    
    // Free memory
    for (i = 0; i < m; i++) {
        free(ata[i]);
    }
    free(ata);
    free(atb);
}

int main() {
    printf("Hello farmer! Let's solve the amount of fertilizers that you should use for each of your crop, considering the number of fields and crops you have!\n");
    
    // Define the fertilizer usage for each crop in each field
    int n, m, i, j;
    printf("How many fields do you have? ");
    scanf("%d", &n);
    printf("How many crops do you have? ");
    scanf("%d", &m);
    
    float** fertilizer_usage = (float**)malloc(n * sizeof(float*));
    for (i = 0; i < n; i++) {
        fertilizer_usage[i] = (float*)malloc(m * sizeof(float));
    }
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            printf("Enter the fertilizer usage for crop %d in field %d: ", j + 1, i + 1);
            scanf("%f", &fertilizer_usage[i][j]);
        }
    }
    
    // Define max fertilizer available for each field
    float* max_fertilizer = (float*)malloc(n * sizeof(float));
    for (i = 0; i < n; i++) {
        printf("Enter the maximum fertilizer available for field %d: ", i + 1);
        scanf("%f", &max_fertilizer[i]);
    }
    
    // Allocate memory for the solution
    float* solution = (float*)malloc(m * sizeof(float));
    
    // Use the lstsq() function to solve the system of equations
    lstsq(n, m, fertilizer_usage, max_fertilizer, solution);
    
    // Print the solution
    printf("Here you go! The amount of fertilizers needed for each crop is:\n");
    for (i = 0; i < m; i++) {
        printf("%.2f ", solution[i]);
    }
    
    // Free memory
    for (i = 0; i < n; i++) {
        free(fertilizer_usage[i]);
    }
    free(fertilizer_usage);
    free(max_fertilizer);
    free(solution);
    
    return 0;
}
