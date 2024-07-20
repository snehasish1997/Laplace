#ifndef FILE_READER_H
#define FILE_READER_H

int read_num_of_temps(const char *filename);
double* read_temps(const char *filename, int numOfTemps);
void write_to_output_file(const char *filename, double *results, int numOfTemps);

#endif // FILE_READER_H