#include "../include/sorts.h"
#include <stdlib.h>

/* ===================================== */
/* Fonction utilitaire                   */
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
/* 1.b Tri à bulles optimisé             */
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

/**
 * @brief Extrait le i-ème chiffre d'un nombre
 * @param x Le nombre
 * @param i Position du chiffre (0 = unités, 1 = dizaines, etc.)
 * @return Le chiffre à la position i
 */
static int cle(int x, int i) {
    while (i-- > 0)
        x /= 10;
    return x % 10;
}

/**
 * @brief Tri auxiliaire par comptage pour une position de chiffre donnée
 * @param T Tableau à trier
 * @param n Taille du tableau
 * @param i Position du chiffre à considérer
 */
static void TriAux(int T[], int n, int i) {
    int count[10] = {0};
    int *output = (int *)malloc(n * sizeof(int));
    
    if (output == NULL) return;

    // Compte les occurrences
    for (int j = 0; j < n; j++)
        count[cle(T[j], i)]++;

    // Calcule les positions cumulatives
    for (int j = 1; j < 10; j++)
        count[j] += count[j - 1];

    // Construit le tableau de sortie
    for (int j = n - 1; j >= 0; j--) {
        int k = cle(T[j], i);
        output[count[k] - 1] = T[j];
        count[k]--;
    }

    // Copie le résultat dans le tableau original
    for (int j = 0; j < n; j++)
        T[j] = output[j];

    free(output);
}

void TriBase(int T[], int n, int k) {
    for (int i = 0; i < k; i++)
        TriAux(T, n, i);
}

/* ===================================== */
/* 4. Tri rapide (Quick Sort)            */
/* ===================================== */

/**
 * @brief Partitionne le tableau autour d'un pivot
 * @param tab Tableau à partitionner
 * @param p Index de début
 * @param r Index de fin
 * @return Position finale du pivot
 */
static int partitionner(int tab[], int p, int r) {
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
/* 5. Tri par tas (Heap Sort)            */
/* ===================================== */

/**
 * @brief Maintient la propriété de tas min pour un nœud
 * @param T Tableau représentant le tas
 * @param n Taille du tas
 * @param i Index du nœud à entasser
 */
static void entasser(int T[], int n, int i) {
    int min = i;
    int fg = 2 * i + 1;  // Fils gauche
    int fd = 2 * i + 2;  // Fils droit

    // Trouve le minimum parmi le nœud et ses fils
    if (fg < n && T[fg] < T[min])
        min = fg;
    if (fd < n && T[fd] < T[min])
        min = fd;

    // Si le minimum n'est pas le nœud actuel, échanger et continuer
    if (min != i) {
        permuter(&T[i], &T[min]);
        entasser(T, n, min);
    }
}

void TriTas(int T[], int n) {
    // Construction du tas
    for (int i = n / 2 - 1; i >= 0; i--)
        entasser(T, n, i);

    // Extraction des éléments du tas un par un
    for (int i = n - 1; i > 0; i--) {
        permuter(&T[0], &T[i]);
        entasser(T, i, 0);
    }
}