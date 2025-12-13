#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Allocation matrices   */
int **allocMat(int n, int m) {
    int **M = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        M[i] = malloc(m * sizeof(int));
    return M;
}

void freeMat(int **M, int n) {
    for (int i = 0; i < n; i++)
        free(M[i]);
    free(M);
}

/* Initialisation triee  */
void initMatTriee(int **M, int n, int m) {
    int val = rand() % 5;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            val += rand() % 3;   // garantit ordre croissant par ligne
            M[i][j] = val;
        }
    }
}

/* sousMat1 : naïve      */
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

/* sousMat2 : optimisee  */
int sousMat2(int **A, int n, int m, int **B, int n1, int m1) {

    for (int i = 0; i <= n - n1; i++) {

        for (int j = 0; j <= m - m1; j++) {

            // Filtrage rapide (lignes triees)
            if (A[i][j] > B[0][0]) continue;
            if (A[i][j + m1 - 1] < B[0][m1 - 1]) continue;

            int ok = 1;

            // Verif premiere ligne
            for (int jj = 0; jj < m1; jj++) {
                if (A[i][j + jj] != B[0][jj]) {
                    ok = 0;
                    break;
                }
            }

            // Verif autres lignes
            for (int ii = 1; ii < n1 && ok; ii++) {

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

int main(int argc, char *argv[]) {

    if (argc != 5) {
        printf("Usage : %s n m n1 m1\n", argv[0]);
        return 1;
    }

    int n  = atoi(argv[1]);
    int m  = atoi(argv[2]);
    int n1 = atoi(argv[3]);
    int m1 = atoi(argv[4]);

    if (n1 > n || m1 > m) {
        printf("Erreur : n1 <= n et m1 <= m\n");
        return 1;
    }

    srand(time(NULL));

    int **A = allocMat(n, m);
    int **B = allocMat(n1, m1);

    initMatTriee(A, n, m);
    initMatTriee(B, n1, m1);

    clock_t t1 = clock();
    int r1 = sousMat1(A, n, m, B, n1, m1);
    clock_t t2 = clock();

    int r2 = sousMat2(A, n, m, B, n1, m1);
    clock_t t3 = clock();

    printf("sousMat1 : %s | Temps = %.6f s\n",
           r1 ? "TROUVEE" : "NON TROUVEE",
           (double)(t2 - t1) / CLOCKS_PER_SEC);

    printf("sousMat2 : %s | Temps = %.6f s\n",
           r2 ? "TROUVEE" : "NON TROUVEE",
           (double)(t3 - t2) / CLOCKS_PER_SEC);

    freeMat(A, n);
    freeMat(B, n1);

    return 0;
}
