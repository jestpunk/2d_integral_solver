#include "fancy_output.h"

void remove_line(void){
    printf("\033[A\33[2KT\r");
}

void print_delimeter(void){
    int WIDTH = 110;
    printf("\n");
    for (int i = 0; i < WIDTH; i++) {
        printf("=");
    }
    printf("\n\n");
}

void print_red(const char* text){
    printf("\033[91m%s\033[0m", text);
}

void print_green(const char* text){
    printf("\033[92m%s\033[0m", text);
}

void print_yellow(const char* text){
    printf("\033[93m%s\033[0m", text);
}

void print_int(int value){
    printf("\033[96m%d\033[0m", value);
}

void print_double(double value){
    printf("\033[96m%e\033[0m", value);
}

void print_info(const char * text){
    print_yellow("[i]");
    printf(" %s", text);
}

void print_error(const char * text){
    print_red("[X]");
    printf(" %s", text);
}

void print_done(const char * text){
    print_green("[V]");
    printf(" %s", text);
}

void print_vector_double(double* v, int n, const char* beginning, const char* ending) {
    int print_size = n < MAX_PRINT ? n : MAX_PRINT;
    int i = 0;

    printf("%s", beginning);
    printf("[");
    for (; i < print_size - 1; i++){
        print_double(v[i]);
        printf(", ");
    }
    print_double(v[i]);
    if (print_size < n)
        printf("...]");
    else
        printf("]");
    printf("%s", ending);
    return;
}

void print_vector_int(int* v, int n, const char* beginning, const char* ending) {
    int print_size = n < MAX_PRINT ? n : MAX_PRINT;
    int i = 0;

    printf("%s", beginning);
    printf("[");
    for (; i < print_size - 1; i++){
        print_int(v[i]);
        printf(", ");
    }
    print_double(v[i]);
    if (print_size < n)
        printf("...]");
    else
        printf("]");
    printf("%s", ending);
    return;
}

void print_matrix(double* A, int n, const char* beginning, const char* ending) {
    int print_size = n < MAX_PRINT ? n : MAX_PRINT;
    int j;
    printf("%s", beginning);
    for (int i = 0; i < print_size; i++) {
        printf("|");
        j = 0;
        for(; j < print_size - 1; j++) {
            print_double(A[i * n + j]);
            printf(", ");
        }
        print_double(A[i * n + j]);
        if (print_size < n)
            printf("...|\n");
        else
            printf("|\n");
    }
    if (print_size < n) {
        printf("|");
        for(int i = 0; i < MAX_PRINT; i++) {
            printf("...           ");
        }
        printf(" |");
    }
    printf("%s", ending);
    return;
}

void print_progress_bar(int a, int b) {
    int TOTAL_CHARS = 30;
    int printing_chars = (int)(((double)a / b) * TOTAL_CHARS);
    printf("[");
    for (int i = 0; i < printing_chars; i++){
        printf("■");
    }
    for (int i = printing_chars; i < TOTAL_CHARS; i++) {
        printf("—");
    }
    printf("] (%d / %d)\n", a, b);
    return;
}
