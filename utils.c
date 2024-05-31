#include "utils.h"

double triangle_integral(struct point a,
                         struct point b,
                         struct point c) {
    return area_of_triangle(a, b, c) * (f(a) + f(b) + f(c)) / 3.;
}

double f(struct point p) {
    return p.x * p.x * p.x * p.x + 
           p.x * p.x * p.y * p.y +
           p.y * p.y * p.y * p.y;
}

int num_edges(int N) {
    return 4 * N + 2 * N * (N - 1) + N * N;
}

int border_idx_of_edge_idx(int idx, int N) {
    
    // Нижняя граница
    if ((idx < 3 * N) && (idx % 3 == 0)) {
        return 1;
    }

    // правая граница
    if ((idx >= num_edges(N) - 2 * N) && 
        (idx < num_edges(N) - N))
        return 2;

    // верхняя граница
    if ((idx >= num_edges(N) - N)) {
        return 3;
    }

    // Левая граница
    if (idx % (3 * N) == 1) {
        return 4;
    }

    return 0;
}

double area_of_triangle(struct point a,
                        struct point b,
                        struct point c) {
    double precision = 1e-8;
    if (fabs(a.x - b.x) < precision) {
        if (fabs(a.y - c.y) < precision) {
            return fabs(a.y - b.y) * fabs(a.x - c.x) * 0.5;
        } else if (fabs(b.y - c.y) < precision) {
            return fabs(a.y - b.y) * fabs(b.x - c.x) * 0.5;
        }
    } else if (fabs(a.x - c.x) < precision) {
        if (fabs(a.y - b.y) < precision) {
            return fabs(a.y - c.y) * fabs(a.x - b.x) * 0.5;
        } else if (fabs(c.y - b.y) < precision) {
            return fabs(a.y - c.y) * fabs(c.x - b.x) * 0.5;
        }
    } else if (fabs(b.x - c.x) < precision) {
        if (fabs(b.y - a.y) < precision) {
            return fabs(b.y - c.y) * fabs(b.x - a.x) * 0.5;
        } else if (fabs(c.y - a.y) < precision) {
            return fabs(b.y - c.y) * fabs(c.x - a.x) * 0.5;
        }
    }
    print_error("");
    printf("Untracked keys in trangle area:\n\t(%e %e), (%e %e), (%e %e)\n\n", a.x, a.y, b.x, b.y, c.x, c.y);
    return 1e10;
}

void fill_points(struct point* points, double x_min, double x_max, double y_min, double y_max, int N) {
    int i, j;
    double x_delta = (x_max - x_min) / (double)N;
    double y_delta = (y_max - y_min) / (double)N;

    for (i = 0; i < N + 1; i++) {
        for (j = 0; j < N + 1; j++) {
            points[i * (N + 1) + j].x = x_min + j * x_delta;
            points[i * (N + 1) + j].y = y_min + i * y_delta;
            //printf("Filled points[%d]\n", i * (N + 1) + j);
        }
    }

    return;
}


void print_points(struct point* points, int N) {
    int N_PRINT = (N + 1) * (N + 1) > MAX_PRINT ? 
                  MAX_PRINT : 
                  (N + 1) * (N + 1);
    for (int i = 0; i < N_PRINT; i++) {
        printf("Point[%d]: (%e %e)\n", i, points[i].x, points[i].y);
    }
    if (N_PRINT < (N + 1) * (N + 1)) {
        printf("...\n");
    }
    return;
}


void fill_triangles(struct triangle* triangles, int N) {
    //int base_point_id;
    int base_point_id_x;
    int base_point_id_y;

    for (int i = 0; i < 2 * N * N; i++) {
        //base_point_id = ( * (N + 1)) + ((i / 2) % 2);
        base_point_id_y = (i / 2 / N);
        base_point_id_x = (i / 2 % N);

        if (i % 2 == 0) {
            triangles[i].a_idx = base_point_id_y * (N + 1) + base_point_id_x;
            triangles[i].b_idx = (base_point_id_y + 1) * (N + 1) + base_point_id_x;
            triangles[i].c_idx = base_point_id_y * (N + 1) + base_point_id_x + 1;
        }
        else {
            triangles[i].a_idx = (base_point_id_y + 1) * (N + 1) + base_point_id_x + 1;
            triangles[i].b_idx = (base_point_id_y + 1) * (N + 1) + base_point_id_x;
            triangles[i].c_idx = base_point_id_y * (N + 1) + base_point_id_x + 1;
        }
    }
    return;
}


void print_triangles(struct triangle* triangles, int N) {
    int N_PRINT = 2 * N * N > MAX_PRINT ? 
                  MAX_PRINT : 
                  2 * N * N;
    for (int i = 0; i < N_PRINT; i++) {
        printf("triangle[%d]: %d %d %d\n", i, triangles[i].a_idx,
                                              triangles[i].b_idx,
                                              triangles[i].c_idx);
    }
    if (N_PRINT < 2 * N * N) {
        printf("...\n");
    }
    return;
}


void fill_edges(struct edge* edges, struct triangle* triangles,  int N) {
    int i;
    int j = 0;

    // Все внутренние точки, ассоциированные с 
    // треугольниками чётного индекса,
    // А также левые и нижние граничные точки
    for (i = 0; i < 2 * N * N; i += 2) {
        edges[j].a_idx = triangles[i].a_idx;
        edges[j].b_idx = triangles[i].c_idx;
        j++;

        edges[j].a_idx = triangles[i].a_idx;
        edges[j].b_idx = triangles[i].b_idx;
        j++;

        edges[j].a_idx = triangles[i].b_idx;
        edges[j].b_idx = triangles[i].c_idx;
        j++;
    }

    // Правые граничные точки
    i = 0;
    for (j = num_edges(N) - 2 * N; 
         j < num_edges(N) - N; j++) {
        edges[j].a_idx =      i  * (N + 1) + N;
        edges[j].b_idx = (i + 1) * (N + 1) + N;
        i++;
    }

    // Верхние граничные точки
    i = 0;
    for (j = num_edges(N) - N; 
         j < num_edges(N); j++) {
        edges[j].a_idx = N * (N + 1) + i;
        edges[j].b_idx = N * (N + 1) + i + 1;
        i++;
    }

    return;
}

const char* side_name_from_idx(int idx) {
    switch(idx) {
        case 0:
            return "inner";
        case 1:
            return "bottom";
        case 2:
            return "right";
        case 3:
            return "up";
        case 4:
            return "left";
        default:
            return "UNKOWN_SIDE_NAME";
    }
}

void print_edges(struct edge* edges, int N) {
    int N_PRINT = num_edges(N) > MAX_PRINT ? 
                  MAX_PRINT : 
                  num_edges(N);
    for (int i = 0; i < N_PRINT; i++) {
        printf("edge[%d]: %d %d [%s]\n", i, 
                                         edges[i].a_idx,
                                         edges[i].b_idx, 
                                         side_name_from_idx(border_idx_of_edge_idx(i, N)));
    }
    if (N_PRINT < num_edges(N)) {
        printf("...\n");
    }
    return;
}


void print_to_file(struct point* points, 
                   struct triangle* triangles, 
                   struct edge* edges,
                   int N, FILE* fp) {
    int i;
    fprintf(fp, "N:\n%d\n", N);
    fprintf(fp, "Число вершин:\n%d\n", (N + 1) * (N + 1));
    fprintf(fp, "Число треугольников:\n%d\n", 2 * N * N);
    fprintf(fp, "Число рёбер:\n%d\n", num_edges(N));

    fprintf(fp, "\nВершины:\n");
    for (i = 0; i < (N + 1) * (N + 1); i++) {
        fprintf(fp, "%d %e %e\n", i, points[i].x, points[i].y);
    }

    fprintf(fp, "\nТреугольники:\n");
    for (i = 0; i < 2 * N * N; i++) {
        fprintf(fp, "%d %d %d %d\n", i, triangles[i].a_idx,
                                                 triangles[i].b_idx,
                                                 triangles[i].c_idx);
    }

    fprintf(fp, "\nРёбра:\n");
    for (i = 0; i < num_edges(N); i++) {
        fprintf(fp, "%d %d %d\n", i, edges[i].a_idx, edges[i].b_idx);
    }
    return;
}

void skip_line(FILE* fp, char* buf) {
    fgets(buf, 1000, fp);
}

void scan_from_file(FILE* fp, 
                    struct point* points, 
                    struct triangle* triangles, 
                    struct edge* edges,
                    int* N) {

    char buf[1000];
    int num_of_triangles, num_of_edges, num_of_points;
    int tmp;

    skip_line(fp, buf);
    skip_line(fp, buf);
    fscanf(fp, "%d", &num_of_points);
    skip_line(fp, buf);
    skip_line(fp, buf);
    fscanf(fp, "%d", &num_of_triangles);
    skip_line(fp, buf);
    skip_line(fp, buf);
    fscanf(fp, "%d", &num_of_edges);
    
    skip_line(fp, buf);
    skip_line(fp, buf);
    skip_line(fp, buf);

    print_done("");
    printf("\nN = %d\nnum_of_points = %d\nnum_of_triangles = %d\nnum_of_edges = %d\n", *N,
                                                                                     num_of_points,
                                                                                     num_of_triangles,
                                                                                     num_of_edges);

    //============================================================

    for (int i = 0; i < num_of_points; i++) {
        fscanf(fp, "%d %lf %lf", &tmp, &points[i].x, &points[i].y);
    }
    skip_line(fp, buf);
    skip_line(fp, buf);
    skip_line(fp, buf);

    for (int i = 0; i < num_of_triangles; i++) {
        fscanf(fp, "%d %d %d %d", &tmp, &triangles[i].a_idx, 
                                        &triangles[i].b_idx, 
                                        &triangles[i].c_idx);

    }
    skip_line(fp, buf);
    skip_line(fp, buf);
    skip_line(fp, buf); 

    for (int i = 0; i < num_of_edges; i++) {
        fscanf(fp, "%d %d %d", &tmp, &edges[i].a_idx, 
                                     &edges[i].b_idx);

    }

    return;
}

double calc_integral(struct triangle* triangles, 
              struct point* points,
              int N) {
    double ans = 0.;
    for (int i = 0; i < 2 * N * N; i++) {
        ans += triangle_integral(points[triangles[i].a_idx],
                                 points[triangles[i].b_idx],
                                 points[triangles[i].c_idx]);
    }
    return ans;
}

































