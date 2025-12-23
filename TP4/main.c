#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Inclusion des fonctions de tri depuis Tp4.c
#include "Tp4.c"

#define NB_TESTS 5
#define NB_TAILLES 10

typedef struct {
    char nom[20];
    void (*tri)(int[], int);
} Algo;

void TriRapideWrap(int t[], int n) {
    TriRapide(t, 0, n-1);
}

void TriBaseWrap(int t[], int n) {
    TriBase(t, n, 5);
}

void generer(int t[], int n) {
    for (int i = 0; i < n; i++) 
        t[i] = rand() % 100000;
}

int verifier(int t[], int n) {
    for (int i = 0; i < n-1; i++)
        if (t[i] > t[i+1]) 
            return 0;
    return 1;
}

double test_algo(Algo algo, int n) {
    int *original = malloc(n * sizeof(int));
    int *copie = malloc(n * sizeof(int));
    double total = 0;
    
    for (int test = 0; test < NB_TESTS; test++) {
        generer(original, n);
        for (int i = 0; i < n; i++) 
            copie[i] = original[i];
        
        clock_t start = clock();
        algo.tri(copie, n);
        clock_t end = clock();
        
        if (! verifier(copie, n)) {
            printf("ERREUR: %s\n", algo.nom);
            free(original);
            free(copie);
            return -1;
        }
        
        total += ((double)(end - start)) * 1000000 / CLOCKS_PER_SEC;
    }
    
    free(original);
    free(copie);
    return total / NB_TESTS;
}

void afficher_tableau(int t[], int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", t[i]);
        if (i < n-1) printf(", ");
    }
    printf("]\n");
}

void test_correction_tritas() {
    printf("\n=== TEST DE CORRECTION TriTas ===\n");
    
    int test1[] = {5, 2, 8, 1, 9};
    int n1 = 5;
    
    printf("Avant tri:  ");
    afficher_tableau(test1, n1);
    
    TriTas(test1, n1);
    
    printf("Apres tri: ");
    afficher_tableau(test1, n1);
    
    if (verifier(test1, n1)) {
        printf("TriTas fonctionne correctement!\n");
    } else {
        printf("TriTas a encore un probleme!\n");
    }
}

int main() {
    srand(time(NULL));
    
    printf("===== BENCHMARK DES ALGORITHMES DE TRI =====\n");
    
    // Test rapide de TriTas
    test_correction_tritas();
    
    // Définition des algorithmes
    Algo algos[6] = {
        {"TriBulle", TriBulle},
        {"TriBulleOpt", TriBulleOpt},
        {"TriGnome", TriGnome},
        {"TriBase", TriBaseWrap},
        {"TriRapide", TriRapideWrap},
        {"TriTas", TriTas}
    };
    
    int tailles[] = {100, 200, 500, 800, 1000, 1500, 2000, 3000, 5000, 10000};
    
    // Création du fichier CSV
    FILE *csv = fopen("resultats.csv", "w");
    if (csv == NULL) {
        printf("Erreur:  impossible de creer le fichier CSV\n");
        return 1;
    }
    
    // En-tête du CSV
    fprintf(csv, "Taille(n)");
    for (int a = 0; a < 6; a++) {
        fprintf(csv, ";%s", algos[a].nom);
    }
    fprintf(csv, "\n");
    
    // Tests pour chaque taille
    printf("\n=== TESTS DE PERFORMANCE ===\n");
    for (int i = 0; i < NB_TAILLES; i++) {
        int n = tailles[i];
        printf("\nn = %d:\n", n);
        fprintf(csv, "%d", n);
        
        for (int a = 0; a < 6; a++) {
            printf("  Testing %s...  ", algos[a].nom);
            fflush(stdout);
            
            double temps = test_algo(algos[a], n);
            
            if (temps >= 0) {
                printf("%. 2f us\n", temps);
                fprintf(csv, ";%.2f", temps);
            } else {
                printf("ERREUR\n");
                fprintf(csv, ";ERREUR");
            }
        }
        fprintf(csv, "\n");
    }
    
    fclose(csv);
    
    printf("\n=== RESUME ===\n");
    printf("Tests termines\n");
    printf("Resultats sauvegardes dans:  resultats.csv\n");
    printf("\nOuvrez resultats.csv avec Excel ou LibreOffice pour voir les resultats.\n");
    
    return 0;
}