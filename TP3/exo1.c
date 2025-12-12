#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* alloue une matrice n x m */
double *alloc_mat(int n, int m){
    return (double*) malloc(sizeof(double) * n * m);
}

/* acces element (i,j) (0-index) */
static inline double get(double *A, int n, int m, int i, int j){
    return A[i*m + j];
}
static inline void set(double *A, int n, int m, int i, int j, double v){
    A[i*m + j] = v;
}

int main(int argc, char **argv){
    if(argc < 4){
        printf("Usage: %s n m p\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int p = atoi(argv[3]);

    double *A = alloc_mat(n,m);
    double *B = alloc_mat(m,p);
    double *C = alloc_mat(n,p);

    /* initialisation (exemple random) */
    srand(0);
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) A[i*m + j] = (double)(rand()%10);
    for(int i=0;i<m;i++) for(int j=0;j<p;j++) B[i*p + j] = (double)(rand()%10);
    for(int i=0;i<n;i++) for(int j=0;j<p;j++) C[i*p + j] = 0.0;

    /* mesure temps */
    clock_t t1 = clock();

    for(int i=0;i<n;i++){
        for(int j=0;j<p;j++){
            double s = 0.0;
            for(int k=0;k<m;k++){
                s += A[i*m + k] * B[k*p + j];
            }
            C[i*p + j] = s;
        }
    }

    clock_t t2 = clock();
    double elapsed = (double)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Temps (s) = %.6f\n", elapsed);

    /* liberation */
    free(A); free(B); free(C);
    return 0;
}
