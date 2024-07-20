#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

double get_final_temperatures(int N, int maxIter, double radTemp) {
    double curr_t[2][N][N];
    int radiator_start = floor((N-1) * 0.3);
    int radiator_end = ceil((N-1) * 0.7);
    
    // Initialize the room temperature array
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == N-1 && j >= radiator_start && j <= radiator_end) {
                curr_t[0][i][j] = radTemp;
            } else {
                curr_t[0][i][j] = 10.0;
            }
        }
    }

    for (int iter = 0; iter < maxIter; iter++) {
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < N-1; i++) {
            for (int j = 1; j < N-1; j++) {
                curr_t[1][i][j] = 0.25 * (curr_t[0][i+1][j] + curr_t[0][i-1][j] + curr_t[0][i][j+1] + curr_t[0][i][j-1]);
            }
        }

        // Swap pointers
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < N-1; i++) {
            for (int j = 1; j < N-1; j++) {
                curr_t[0][i][j] = curr_t[1][i][j];
            }
        }
    }

    int pointx = floor((N-1) * 0.5);
    int pointy = floor((N-1) * 0.5);
    double result = curr_t[0][pointx][pointy];
    return result;
}
