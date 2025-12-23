#include <stdio.h>
#include <stdlib.h>

/* ===================================== */
/* Outil de permutation                  */
/* ===================================== */
void permuter(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ===================================== */
/* 1. Tri à bulles                       */
/* ===================================== */
void TriBulle(int T[], int n) {
    int changement = 1;

    while (changement) {
        changement = 0;
        for (int i = 0; i < n - 1; i++) {
            if (T[i] > T[i + 1]) {
                permuter(&T[i], &T[i + 1]);
                changement = 1;
            }
        }
    }
}

/* ===================================== */
/* 1. b Tri à bulles optimisé             */
/* ===================================== */
void TriBulleOpt(int T[], int n) {
    int changement = 1;
    int m = n - 1;

    while (changement) {
        changement = 0;
        for (int i = 0; i < m; i++) {
            if (T[i] > T[i + 1]) {
                permuter(&T[i], &T[i + 1]);
                changement = 1;
            }
        }
        m--;
    }
}

/* ===================================== */
/* 2. Tri Gnome                          */
/* ===================================== */
void TriGnome(int T[], int n) {
    int i = 0;

    while (i < n) {
        if (i == 0 || T[i] >= T[i - 1])
            i++;
        else {
            permuter(&T[i], &T[i - 1]);
            i--;
        }
    }
}

/* ===================================== */
/* 3. Tri par base (Radix Sort)          */
/* ===================================== */

/* Fonction clé */
int cle(int x, int i) {
    while (i-- > 0)
        x /= 10;
    return x % 10;
}

/* Tri auxiliaire */
void TriAux(int T[], int n, int i) {
    int count[10] = {0};
    int output[n];

    for (int j = 0; j < n; j++)
        count[cle(T[j], i)]++;

    for (int j = 1; j < 10; j++)
        count[j] += count[j - 1];

    for (int j = n - 1; j >= 0; j--) {
        int k = cle(T[j], i);
        output[count[k] - 1] = T[j];
        count[k]--;
    }

    for (int j = 0; j < n; j++)
        T[j] = output[j];
}

/* Tri par base */
void TriBase(int T[], int n, int k) {
    for (int i = 0; i < k; i++)
        TriAux(T, n, i);
}

/* ===================================== */
/* 4. Tri rapide                         */
/* ===================================== */
int partitionner(int tab[], int p, int r) {
    int pivot = tab[p];
    int i = p - 1;
    int j = r + 1;

    while (1) {
        do { j--; } while (tab[j] > pivot);
        do { i++; } while (tab[i] < pivot);

        if (i < j)
            permuter(&tab[i], &tab[j]);
        else
            return j;
    }
}

void TriRapide(int tab[], int p, int r) {
    if (p < r) {
        int q = partitionner(tab, p, r);
        TriRapide(tab, p, q);
        TriRapide(tab, q + 1, r);
    }
}

/* ===================================== */
/* 5. Tri par tas (Heap Sort) - CORRIGÉ */
/* ===================================== */
void entasser(int T[], int n, int i) {
    int max = i;
    int fg = 2 * i + 1;
    int fd = 2 * i + 2;

    // Chercher le MAXIMUM (pour tri croissant)
    if (fg < n && T[fg] > T[max])
        max = fg;
    if (fd < n && T[fd] > T[max])
        max = fd;

    if (max != i) {
        permuter(&T[i], &T[max]);
        entasser(T, n, max);
    }
}

void TriTas(int T[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasser(T, n, i);

    for (int i = n - 1; i > 0; i--) {
        permuter(&T[0], &T[i]);
        entasser(T, i, 0);
    }
}