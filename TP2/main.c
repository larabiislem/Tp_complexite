#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "algos.h"

// Tailles à tester selon l'énoncé
int sizes[] = {100000, 200000, 400000, 600000, 800000, 1000000, 1200000, 1400000, 1600000, 1800000};
int num_sizes = 10;

// Nombre de répétitions pour avoir des mesures précises
#define REPETITIONS 1000

// ==================== PARTIE A: Tests de recherche ====================

void testPartieA()
{
    printf("\n========== PARTIE A: Recherche d'elements ==========\n\n");

    printf("%-20s", "n");
    for (int i = 0; i < num_sizes; i++)
    {
        printf("%10d", sizes[i]);
    }
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    // Pour chaque taille
    double temps_non_trie_meilleur[10], temps_non_trie_pire[10];
    double temps_trie_meilleur[10], temps_trie_pire[10];
    double temps_dicho_meilleur[10], temps_dicho_pire[10];

    for (int s = 0; s < num_sizes; s++)
    {
        int n = sizes[s];
        int *T = (int *)malloc(n * sizeof(int));
        int *T_trie = (int *)malloc(n * sizeof(int));

        // Remplir avec valeurs aléatoires (non trié) et triées (directement)
        remplirTableauAleatoire(T, n);
        remplirTableauTrie(T_trie, n);

        clock_t start, end;
        int i;

        // --- Tableau Non Trié ---
        // Meilleur cas: élément au début
        int x_meilleur = T[0];
        start = clock();
        for (i = 0; i < REPETITIONS; i++)
            rechElets_TabNonTries(T, n, x_meilleur);
        end = clock();
        temps_non_trie_meilleur[s] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / REPETITIONS;

        // Pire cas: élément inexistant
        int x_pire = -999999;
        start = clock();
        for (i = 0; i < REPETITIONS; i++)
            rechElets_TabNonTries(T, n, x_pire);
        end = clock();
        temps_non_trie_pire[s] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / REPETITIONS;

        // --- Tableau Trié (séquentiel) ---
        // Meilleur cas: élément au début
        x_meilleur = T_trie[0];
        start = clock();
        for (i = 0; i < REPETITIONS; i++)
            rechElets_TabTries(T_trie, n, x_meilleur);
        end = clock();
        temps_trie_meilleur[s] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / REPETITIONS;

        // Pire cas: élément à la fin ou inexistant plus grand
        x_pire = T_trie[n - 1] + 1;
        start = clock();
        for (i = 0; i < REPETITIONS; i++)
            rechElets_TabTries(T_trie, n, x_pire);
        end = clock();
        temps_trie_pire[s] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / REPETITIONS;

        // --- Recherche Dichotomique ---
        // Meilleur cas: élément au milieu
        x_meilleur = T_trie[n / 2];
        start = clock();
        for (i = 0; i < REPETITIONS; i++)
            rechElets_Dicho(T_trie, n, x_meilleur);
        end = clock();
        temps_dicho_meilleur[s] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / REPETITIONS;

        // Pire cas: élément inexistant
        x_pire = -999999;
        start = clock();
        for (i = 0; i < REPETITIONS; i++)
            rechElets_Dicho(T_trie, n, x_pire);
        end = clock();
        temps_dicho_pire[s] = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / REPETITIONS;

        free(T);
        free(T_trie);

        printf("  Taille %d terminee...\n", n);
    }

    // Affichage du tableau
    printf("\n%-20s", "n");
    for (int i = 0; i < num_sizes; i++)
        printf("%10d", sizes[i]);
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------\n");

    printf("%-20s", "NonTrie Meilleur");
    for (int i = 0; i < num_sizes; i++)
        printf("%10.2f", temps_non_trie_meilleur[i]);
    printf(" (us)\n");

    printf("%-20s", "NonTrie Pire");
    for (int i = 0; i < num_sizes; i++)
        printf("%10.2f", temps_non_trie_pire[i]);
    printf(" (us)\n");

    printf("%-20s", "Trie Meilleur");
    for (int i = 0; i < num_sizes; i++)
        printf("%10.2f", temps_trie_meilleur[i]);
    printf(" (us)\n");

    printf("%-20s", "Trie Pire");
    for (int i = 0; i < num_sizes; i++)
        printf("%10.2f", temps_trie_pire[i]);
    printf(" (us)\n");

    printf("%-20s", "Dicho Meilleur");
    for (int i = 0; i < num_sizes; i++)
        printf("%10.2f", temps_dicho_meilleur[i]);
    printf(" (us)\n");

    printf("%-20s", "Dicho Pire");
    for (int i = 0; i < num_sizes; i++)
        printf("%10.2f", temps_dicho_pire[i]);
    printf(" (us)\n");

    // Exporter en CSV pour le graphique
    FILE *f = fopen("resultats_recherche.csv", "w");
    if (f)
    {
        fprintf(f, "n,NonTrie_Pire,Trie_Pire,Dicho_Pire\n");
        for (int i = 0; i < num_sizes; i++)
        {
            fprintf(f, "%d,%.2f,%.2f,%.2f\n", sizes[i],
                    temps_non_trie_pire[i], temps_trie_pire[i], temps_dicho_pire[i]);
        }
        fclose(f);
        printf("\n=> Resultats exportes dans 'resultats_recherche.csv'\n");
    }
}

// ==================== PARTIE B: Tests Max et Min ====================

void testPartieB()
{
    printf("\n\n========== PARTIE B: Recherche Max et Min ==========\n\n");

    printf("--- Comparaison du nombre de comparaisons ---\n");
    printf("%-15s%-20s%-20s%-15s\n", "n", "MaxEtMinA", "MaxEtMinB", "Gain");
    printf("----------------------------------------------------------------\n");

    int test_sizes[] = {100, 1000, 10000, 100000, 500000, 1000000};
    int num_test = 6;

    for (int s = 0; s < num_test; s++)
    {
        int n = test_sizes[s];
        int *T = (int *)malloc(n * sizeof(int));
        int *T_copy = (int *)malloc(n * sizeof(int));

        remplirTableauAleatoire(T, n);

        int minA, maxA, minB, maxB;
        int compA, compB;

        copierTableau(T, T_copy, n);
        MaxEtMinA_Count(T_copy, n, &minA, &maxA, &compA);

        copierTableau(T, T_copy, n);
        MaxEtMinB_Count(T_copy, n, &minB, &maxB, &compB);

        double gain = ((double)(compA - compB) / compA) * 100;

        printf("%-15d%-20d%-20d%-15.2f%%\n", n, compA, compB, gain);

        free(T);
        free(T_copy);
    }

    // Complexité théorique
    printf("\n--- Complexite theorique ---\n");
    printf("MaxEtMinA: 2(n-1) comparaisons\n");
    printf("MaxEtMinB: 3n/2 - 2 comparaisons (environ)\n");

    // Test de temps d'exécution
    printf("\n--- Comparaison des temps d'execution (us) ---\n");
    printf("%-15s%-20s%-20s\n", "n", "MaxEtMinA", "MaxEtMinB");
    printf("------------------------------------------------\n");

    int reps_b[] = {100000, 10000, 1000, 100, 20, 10}; // répétitions adaptées à la taille

    for (int s = 0; s < num_test; s++)
    {
        int n = test_sizes[s];
        int *T = (int *)malloc(n * sizeof(int));
        int *T_copy = (int *)malloc(n * sizeof(int));
        int reps = reps_b[s];

        remplirTableauAleatoire(T, n);

        int minVal, maxVal;
        clock_t start, end;

        // Test MaxEtMinA
        start = clock();
        for (int r = 0; r < reps; r++)
        {
            copierTableau(T, T_copy, n);
            MaxEtMinA(T_copy, n, &minVal, &maxVal);
        }
        end = clock();
        double tempsA = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / reps;

        // Test MaxEtMinB
        start = clock();
        for (int r = 0; r < reps; r++)
        {
            copierTableau(T, T_copy, n);
            MaxEtMinB(T_copy, n, &minVal, &maxVal);
        }
        end = clock();
        double tempsB = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000 / reps;

        printf("%-15d%-20.2f%-20.2f\n", n, tempsA, tempsB);

        free(T);
        free(T_copy);
    }

    // Exporter en CSV
    FILE *f = fopen("resultats_maxmin.csv", "w");
    if (f)
    {
        fprintf(f, "n,MaxEtMinA_comparisons,MaxEtMinB_comparisons,MaxEtMinA_time,MaxEtMinB_time\n");
        for (int s = 0; s < num_test; s++)
        {
            int n = test_sizes[s];
            int *T = (int *)malloc(n * sizeof(int));
            int *T_copy = (int *)malloc(n * sizeof(int));

            remplirTableauAleatoire(T, n);

            int minVal, maxVal, compA, compB;
            clock_t start, end;

            copierTableau(T, T_copy, n);
            start = clock();
            MaxEtMinA_Count(T_copy, n, &minVal, &maxVal, &compA);
            end = clock();
            double tempsA = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

            copierTableau(T, T_copy, n);
            start = clock();
            MaxEtMinB_Count(T_copy, n, &minVal, &maxVal, &compB);
            end = clock();
            double tempsB = ((double)(end - start)) / CLOCKS_PER_SEC * 1000000;

            fprintf(f, "%d,%d,%d,%.2f,%.2f\n", n, compA, compB, tempsA, tempsB);

            free(T);
            free(T_copy);
        }
        fclose(f);
        printf("\n=> Resultats exportes dans 'resultats_maxmin.csv'\n");
    }
}

int main()
{
    // Initialiser le générateur aléatoire
    srand(time(NULL));

    printf("TP2 - Algorithmique avancee et complexite\n");
    printf("Recherche d'elements et Min/Max\n");
    printf("=========================================\n");

    // Exécuter les tests Partie A
    testPartieA();

    // Exécuter les tests Partie B
    testPartieB();

    printf("\n\n========== FIN DES TESTS ==========\n");

    return 0;
}
