#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fancy_output.h"
#include "utils.h"

// USAGE
// ./2D_integral_solver setup N x_min x_max y_min y_max
//
int main(int argc, const char** argv) {
    int N;
    double x_min;
    double x_max;
    double y_min;
    double y_max;
    
    FILE* fp;

    struct point* points;
    struct triangle* triangles;
    struct edge* edges;

    char buf[1000];
    double calculated_integral_value;

    if (argc < 2) {
        printf("Too few args\n");
        return -1;
    }

    if (strcmp(argv[1], "setup") == 0) {
        if (argc < 7) {
            printf("Too few args\n");
            return -1;
        }

        N = atoi(argv[2]);
        x_min = atof(argv[3]);
        x_max = atof(argv[4]);
        y_min = atof(argv[5]);
        y_max = atof(argv[6]);
        
        points = (struct point*)malloc((N + 1) * (N + 1) * sizeof(struct point));
        triangles = (struct triangle*)malloc(2 * N * N * sizeof(struct triangle));
        edges = (struct edge*)malloc(((4 * N) + 2 * N * (N - 1) + N * N) * sizeof(struct edge));

        if(!points || !triangles || !edges) {
            printf("Allocation error!\n");
            return -1;
        }

        fp = fopen("grid.txt", "w");
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
        { // initialization
        fp = fopen("grid.txt", "r");
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
        //print_points(points, N);
        //print_triangles(triangles, N);
        //print_edges(edges, N);
        }

        calculated_integral_value = calc_integral(triangles, points, N);
        printf("Integral:  %e\n", calculated_integral_value);

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
