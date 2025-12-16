#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Allocation d'une matrice n x m */
double *alloc_mat(int n, int m){
    return (double*) malloc(sizeof(double) * n * m);
}

int main(){
    FILE *f = fopen("temps_multiplication.csv", "w");
    if(!f){
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return 1;
    }

    fprintf(f, "n,Temps(s)\n");
    printf("=== Test du produit matriciel ===\n");

    srand(0);

    /* Valeurs de n choisies dans [100, 10000] */
    int valeurs_n[] = {100, 200, 500, 1000, 2000, 3000, 5000};
    int nb_tests = sizeof(valeurs_n) / sizeof(int);

    for(int t = 0; t < nb_tests; t++){
        int n = valeurs_n[t];
        int m = n;
        int p = n;

        double *A = alloc_mat(n, m);
        double *B = alloc_mat(m, p);
        double *C = alloc_mat(n, p);

        if(!A || !B || !C){
            printf("Erreur allocation mémoire pour n=%d\n", n);
            return 1;
        }

        /* Initialisation */
        for(int i = 0; i < n*m; i++) A[i] = rand() % 10;
        for(int i = 0; i < m*p; i++) B[i] = rand() % 10;
        for(int i = 0; i < n*p; i++) C[i] = 0.0;

        /* Mesure du temps */
        clock_t t1 = clock();

        for(int i = 0; i < n; i++){
            for(int j = 0; j < p; j++){
                double s = 0.0;
                for(int k = 0; k < m; k++){
                    s += A[i*m + k] * B[k*p + j];
                }
                C[i*p + j] = s;
            }
        }

        clock_t t2 = clock();
        double T = (double)(t2 - t1) / CLOCKS_PER_SEC;

        printf("n = %5d | Temps = %.6f s\n", n, T);
        fprintf(f, "%d,%.6f\n", n, T);

        free(A);
        free(B);
        free(C);
    }

    fclose(f);
    printf("\nRésultats sauvegardés dans : temps_multiplication.csv\n");

    return 0;
}

