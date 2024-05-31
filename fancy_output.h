#ifndef FANCY_OUTPUT_H
#define FANCY_OUTPUT_H

#include <stdio.h>

#define MAX_PRINT 6
#define MAX_N_POINTS 20

void remove_line(void);
void print_delimeter(void);

void print_red(const char* text);
void print_green(const char* text);
void print_yellow(const char* text);

void print_info(const char * text);
void print_error(const char * text);
void print_done(const char * text);

void print_int(int value);
void print_double(double value);
void print_vector_double(double* v, int n, const char* beginning, const char* ending);
void print_vector_int(int* v, int n, const char* beginning, const char* ending);
void print_matrix(double* A, int n, const char* beginning, const char* ending);

void print_progress_bar(int a, int b);

#endif // FANCY_OUTPUT_H
