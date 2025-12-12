#include <stdio.h>
#include <stdlib.h>

/*
  Recherche naïve de la sous-matrice B dans A.
  Retourne 1 si trouvée, 0 sinon.
*/

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


/*
  Version optimisee lorsque LES LIGNES DE A ET B SONT TRIÉES.
  Retourne 1 si trouvé, 0 sinon.
*/

int sousMat2(int **A, int n, int m, int **B, int n1, int m1) {

    for (int i = 0; i <= n - n1; i++) {

        for (int j = 0; j <= m - m1; j++) {

            // Filtre rapide sur la premiere ligne (triee)
            if (A[i][j] > B[0][0]) continue;
            if (A[i][j + m1 - 1] < B[0][m1 - 1]) continue;

            // Verification de la premiere ligne
            int ok = 1;
            for (int jj = 0; jj < m1; jj++) {
                if (A[i][j + jj] != B[0][jj]) {
                    ok = 0;
                    break;
                }
            }

            if (!ok) continue;

            // Verification des lignes suivantes
            for (int ii = 1; ii < n1 && ok; ii++) {

                // Filtre rapide car lignes triees
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


int sousMat1(int **A, int n, int m, int **B, int n1, int m1);
int sousMat2(int **A, int n, int m, int **B, int n1, int m1);

int main() {
    int n = 4, m = 5;
    int n1 = 2, m1 = 3;

    // Matrice A
    int **A = malloc(n * sizeof(int*));
    int dataA[4][5] = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
        {4, 5, 6, 7, 8}
    };

    for (int i = 0; i < n; i++)
        A[i] = dataA[i];

    // Matrice B
    int **B = malloc(n1 * sizeof(int*));
    int dataB[2][3] = {
        {4, 5, 6},
        {5, 6, 7}
    };

    for (int i = 0; i < n1; i++)
        B[i] = dataB[i];

    printf("sousMat1 : %d\n", sousMat1(A, n, m, B, n1, m1));
    printf("sousMat2 : %d\n", sousMat2(A, n, m, B, n1, m1));

    free(A);
    free(B);

    return 0;
}