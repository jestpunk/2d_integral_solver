#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fancy_output.h"
#include "utils.h"

/* 3 */
int main(int argc, const char** argv) {
    if (argc < 2) {
        printf("Too few args\n");
        return -1;
    }

    if (strcmp(argv[1], "setup") == 0) {
        int N = 100;
        double x_min = 0.;
        double x_max = 1.;
        double y_min = 0.;
        double y_max = 1.;
        FILE* fp;

        struct point* points;
        struct triangle* triangles;
        struct edge* edges;

        points = (struct point*)malloc((N + 1) * (N + 1) * sizeof(struct point));
        triangles = (struct triangle*)malloc(2 * N * N * sizeof(struct triangle));
        edges = (struct edge*)malloc(((4 * N) + 2 * N * (N - 1) + N * N) * sizeof(struct edge));

        if(!points || !triangles || !edges) {
            printf("Allocation error!\n");
            return -1;
        }

        fp = fopen("output.txt", "w");
        if(!fp) {
            printf("Error open file\n");
            return -1;
        }

        fill_points(points, x_min, x_max, y_min, y_max, N);
        print_points(points, N);

        fill_triangles(triangles, N);
        print_triangles(triangles, N);

        fill_edges(edges, triangles, N);
        print_edges(edges, N);

        print_to_file(points, triangles, edges, N, fp);

        fclose(fp);
        free(points);
        free(triangles);
        free(edges);

        return 0;
    }
    else if (strcmp(argv[1], "calculate") == 0) {
        int N;
        
        FILE* fp;

        struct point* points;
        struct triangle* triangles;
        struct edge* edges;

        char buf[1000];
        double true_integral_value = 23. / 45.;
        double calculated_integral_value;

        { // initialization
        fp = fopen("output.txt", "r");
        if(!fp) {
            printf("Error open file\n");
            return -1;
        }
        skip_line(fp, buf);
        fscanf(fp, "%d", &N);

        points = (struct point*)malloc((N + 1) * (N + 1) * sizeof(struct point));
        triangles = (struct triangle*)malloc(2 * N * N * sizeof(struct triangle));
        edges = (struct edge*)malloc(((4 * N) + 2 * N * (N - 1) + N * N) * sizeof(struct edge));

        if(!points || !triangles || !edges) {
            printf("Allocation error!\n");
            return -1;
        }

        scan_from_file(fp, points, triangles, edges, &N);
        print_points(points, N);
        print_triangles(triangles, N);
        print_edges(edges, N);
        }

        calculated_integral_value = calc_integral(triangles, points, N);
        printf("Real integral: %e\nOur integral:  %e\nDelta:         %e\nlog_N(Delta):  %e", 
               true_integral_value,
               calculated_integral_value,
               fabs(true_integral_value - calculated_integral_value),
               log(fabs(true_integral_value - calculated_integral_value)) / log(N));

        fclose(fp);
        free(points);
        free(triangles);
        free(edges);
        
        return 0;
    }
    else {
        printf("Unkown task\n");
        return -1;
    }
}
