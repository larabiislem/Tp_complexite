#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ================= Allocation ================= */

int **allocMat(int n, int m) {
    int **M = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        M[i] = (int *)malloc(m * sizeof(int));
    return M;
}

void freeMat(int **M, int n) {
    for (int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

/* ================= Initialisation ================= */

/* Matrices NON triées */
void initMatNonTriee(int **M, int n, int m) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            M[i][j] = rand() % 100;
}

/* Matrices triées par ligne */
void initMatTriee(int **M, int n, int m) {
    for (int i = 0; i < n; i++) {
        int val = rand() % 5;
        for (int j = 0; j < m; j++) {
            val += rand() % 3;
            M[i][j] = val;
        }
    }
}

/* ================= sousMat1 ================= */
/* Méthode naïve */

int sousMat1(int **A, int n, int m, int **B, int n1, int m1) {
    for (int i = 0; i <= n - n1; i++) {
        for (int j = 0; j <= m - m1; j++) {
            int ok = 1;
            for (int ii = 0; ii < n1 && ok; ii++) {
                for (int jj = 0; jj < m1; jj++) {
                    if (A[i + ii][j + jj] != B[ii][jj]) {
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok) return 1;
        }
    }
    return 0;
}

/* ================= sousMat2 ================= */
/* Méthode optimisée (tri par ligne) */

int sousMat2(int **A, int n, int m, int **B, int n1, int m1) {
    for (int i = 0; i <= n - n1; i++) {
        for (int j = 0; j <= m - m1; j++) {

            if (A[i][j] > B[0][0]) continue;
            if (A[i][j + m1 - 1] < B[0][m1 - 1]) continue;

            int ok = 1;
            for (int ii = 0; ii < n1 && ok; ii++) {

                if (A[i + ii][j] > B[ii][0]) { ok = 0; break; }
                if (A[i + ii][j + m1 - 1] < B[ii][m1 - 1]) { ok = 0; break; }

                for (int jj = 0; jj < m1; jj++) {
                    if (A[i + ii][j + jj] != B[ii][jj]) {
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok) return 1;
        }
    }
    return 0;
}

/* ==================== MAIN ==================== */

int main() {

    FILE *f = fopen("resultats_sous_matrice.csv", "w");
    if (!f) {
        printf("Erreur ouverture fichier\n");
        return 1;
    }

    fprintf(f, "n,m,n1,m1,Temps_sousMat1,Temps_sousMat2\n");

    srand(time(NULL));

    int taillesA[] = {100, 200, 500, 700, 1000, 2000, 3000};
    int taillesB[] = {2, 3, 4};

    int nbA = sizeof(taillesA) / sizeof(int);
    int nbB = sizeof(taillesB) / sizeof(int);

    int REP = 1000;              /* répétitions */
    volatile int res = 0;        /* empêche l’optimisation */

    for (int a = 0; a < nbA; a++) {
        for (int b = 0; b < nbB; b++) {

            int n = taillesA[a];
            int m = taillesA[a];
            int n1 = taillesB[b];
            int m1 = taillesB[b];

            int **A1 = allocMat(n, m);
            int **B1 = allocMat(n1, m1);

            int **A2 = allocMat(n, m);
            int **B2 = allocMat(n1, m1);

            initMatNonTriee(A1, n, m);
            initMatNonTriee(B1, n1, m1);

            initMatTriee(A2, n, m);
            initMatTriee(B2, n1, m1);

            clock_t t1 = clock();
            for (int r = 0; r < REP; r++)
                res += sousMat1(A1, n, m, B1, n1, m1);
            clock_t t2 = clock();

            for (int r = 0; r < REP; r++)
                res += sousMat2(A2, n, m, B2, n1, m1);
            clock_t t3 = clock();

            double T1 = (double)(t2 - t1) / CLOCKS_PER_SEC / REP;
            double T2 = (double)(t3 - t2) / CLOCKS_PER_SEC / REP;

            printf("n=%d n1=%d | sousMat1=%.6f s | sousMat2=%.6f s\n",
                   n, n1, T1, T2);

            fprintf(f, "%d,%d,%d,%d,%.6f,%.6f\n",
                    n, m, n1, m1, T1, T2);

            freeMat(A1, n);
            freeMat(B1, n1);
            freeMat(A2, n);
            freeMat(B2, n1);
        }
    }

    fclose(f);
    printf("\nRésultats sauvegardés dans resultats_sous_matrice.csv\n");

    return 0;
}
