#include <stdio.h>
#include <stdlib.h>
#include "file-reader.h"
#include "heat.h"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <N> <max_iter> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    int maxIter = atoi(argv[2]);
    char* input_file = argv[3];
    char* output_file = argv[4];

    int numOfTemps = read_num_of_temps(input_file);
    double* radTemps = read_temps(input_file, numOfTemps);
    double* results = (double*)malloc(numOfTemps * sizeof(double));

    for (int i = 0; i < numOfTemps; i++) {
        results[i] = get_final_temperatures(N, maxIter, radTemps[i]);
    }

    write_to_output_file(output_file, results, numOfTemps);

    free(radTemps);
    free(results);

    return 0;
}
