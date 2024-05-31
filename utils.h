#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdlib.h>
#include "fancy_output.h"

struct point {
   double x;
   double y;
};

struct triangle {
   int a_idx;
   int b_idx;
   int c_idx;
};

struct edge {
   int a_idx;
   int b_idx;
};

double triangle_integral(struct point a,
                         struct point b,
                         struct point c);

double area_of_triangle(struct point a,
                        struct point b,
                        struct point c);

void fill_points(struct point* points, double x_min, double x_max, double y_min, double y_max, int N);
void print_points(struct point* points, int N);

void fill_triangles(struct triangle* triangles, int N);
void print_triangles(struct triangle* triangles, int N);

void fill_edges(struct edge* edges, struct triangle* triangles, int N);
void print_edges(struct edge* edges, int N);
int num_edges(int N);
const char* side_name_from_idx(int idx);
int border_idx_of_edge_idx(int idx, int N);

void print_to_file(struct point* points, 
                   struct triangle* triangles, 
                   struct edge* edges,
                   int N, FILE* fp);

void skip_line(FILE* fp, char* buf);

void scan_from_file(FILE* fp, 
                    struct point* points, 
                    struct triangle* triangles, 
                    struct edge* edges,
                    int* N);

double calc_integral(struct triangle* triangles, 
                     struct point* points,
                     int N);

double f(struct point);

\
#endif
