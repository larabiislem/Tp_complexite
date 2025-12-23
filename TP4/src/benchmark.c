#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/sorts.h"
#include "../include/utils.h"

/* ===================================== */
/* Configuration du benchmark            */
/* ===================================== */

#define NB_ITERATIONS 10        // Nombre de répétitions pour chaque test
#define MAX_VALUE 100000        // Valeur maximale des entiers aléatoires
#define NB_CHIFFRES 5          // Nombre de chiffres pour le tri par base
#define FICHIER_RESULTATS "results/benchmark_results.csv"

/* Tailles de tableaux à tester */
const int TAILLES[] = {
    100, 200, 500, 1000, 2000, 3000, 4000, 5000,
    6000, 7000, 8000, 9000, 10000, 15000, 20000
};
const int NB_TAILLES = sizeof(TAILLES) / sizeof(TAILLES[0]);

/* ===================================== */
/* Structure pour les résultats          */
/* ===================================== */

typedef struct {
    const char *nom;
    double temps_moyen;
    double temps_min;
    double temps_max;
    int succes;
} ResultatTri;

/* ===================================== */
/* Fonction de test générique            */
/* ===================================== */

/**
 * @brief Teste un algorithme de tri sur un tableau
 * @param tableau Tableau à trier
 * @param taille Taille du tableau
 * @param type_tri Type d'algorithme (0-5)
 * @return Temps d'exécution en millisecondes, -1 en cas d'erreur
 */
double tester_tri(int tableau[], int taille, int type_tri) {
    clock_t debut, fin;
    
    debut = clock();
    
    switch (type_tri) {
        case 0: // Tri à bulles
            TriBulle(tableau, taille);
            break;
        case 1: // Tri à bulles optimisé
            TriBulleOpt(tableau, taille);
            break;
        case 2: // Tri Gnome
            TriGnome(tableau, taille);
            break;
        case 3: // Tri par base
            TriBase(tableau, taille, NB_CHIFFRES);
            break;
        case 4: // Tri rapide
            TriRapide(tableau, 0, taille - 1);
            break;
        case 5: // Tri par tas
            TriTas(tableau, taille);
            break;
        default:
            return -1.0;
    }
    
    fin = clock();
    
    return temps_ecoule_ms(debut, fin);
}

/* ===================================== */
/* Benchmark complet                     */
/* ===================================== */

/**
 * @brief Effectue un benchmark complet d'un algorithme
 * @param tableau_original Tableau de référence
 * @param taille Taille du tableau
 * @param type_tri Type d'algorithme
 * @param resultat Structure pour stocker les résultats
 */
void benchmark_algorithme(int tableau_original[], int taille, int type_tri, 
                         ResultatTri *resultat) {
    int *tableau_copie = (int *)malloc(taille * sizeof(int));
    if (tableau_copie == NULL) {
        resultat->succes = 0;
        return;
    }
    
    double temps_total = 0.0;
    double temps_min = 1e9;
    double temps_max = 0.0;
    
    // Effectuer plusieurs itérations
    for (int iter = 0; iter < NB_ITERATIONS; iter++) {
        // Copier le tableau original
        copier_tableau(tableau_original, tableau_copie, taille);
        
        // Tester l'algorithme
        double temps = tester_tri(tableau_copie, taille, type_tri);
        
        if (temps < 0) {
            resultat->succes = 0;
            free(tableau_copie);
            return;
        }
        
        // Vérifier que le tableau est bien trié
        if (!verifier_tri(tableau_copie, taille)) {
            printf("ERREUR: Le tableau n'est pas correctement trié!\n");
            resultat->succes = 0;
            free(tableau_copie);
            return;
        }
        
        // Mettre à jour les statistiques
        temps_total += temps;
        if (temps < temps_min) temps_min = temps;
        if (temps > temps_max) temps_max = temps;
    }
    
    // Calculer les résultats
    resultat->temps_moyen = temps_total / NB_ITERATIONS;
    resultat->temps_min = temps_min;
    resultat->temps_max = temps_max;
    resultat->succes = 1;
    
    free(tableau_copie);
}

/* ===================================== */
/* Sauvegarde des résultats              */
/* ===================================== */

/**
 * @brief Initialise le fichier CSV avec les en-têtes
 * @param fichier Pointeur vers le fichier
 */
void initialiser_csv(FILE *fichier) {
    fprintf(fichier, "Taille,Algorithme,Temps_Moyen_ms,Temps_Min_ms,Temps_Max_ms\n");
}

/**
 * @brief Ajoute une ligne de résultats au fichier CSV
 * @param fichier Pointeur vers le fichier
 * @param taille Taille du tableau testé
 * @param resultat Résultats du benchmark
 */
void ajouter_resultat_csv(FILE *fichier, int taille, ResultatTri *resultat) {
    if (resultat->succes) {
        fprintf(fichier, "%d,%s,%.4f,%.4f,%.4f\n",
                taille, resultat->nom,
                resultat->temps_moyen,
                resultat->temps_min,
                resultat->temps_max);
    }
}

/* ===================================== */
/* Affichage des résultats               */
/* ===================================== */

/**
 * @brief Affiche une barre de progression
 * @param progression Pourcentage de progression (0-100)
 */
void afficher_progression(int progression) {
    printf("\rProgression: [");
    int nb_barres = progression / 2;
    for (int i = 0; i < 50; i++) {
        if (i < nb_barres) printf("=");
        else if (i == nb_barres) printf(">");
        else printf(" ");
    }
    printf("] %3d%%", progression);
    fflush(stdout);
}

/**
 * @brief Affiche un tableau de résultats formaté
 * @param taille Taille du tableau testé
 * @param resultats Tableau des résultats
 * @param nb_algos Nombre d'algorithmes testés
 */
void afficher_resultats(int taille, ResultatTri resultats[], int nb_algos) {
    printf("\n\n╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║ RÉSULTATS POUR n = %-6d                                      ║\n", taille);
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    printf("║ %-25s │ %-12s │ %-12s ║\n", 
           "Algorithme", "Temps moyen", "Écart-type");
    printf("╠═══════════════════════════════════════════════════════════════════╣\n");
    
    for (int i = 0; i < nb_algos; i++) {
        if (resultats[i].succes) {
            double ecart_type = (resultats[i].temps_max - resultats[i].temps_min) / 2.0;
            printf("║ %-25s │ %9.3f ms │ %9.3f ms ║\n",
                   resultats[i].nom,
                   resultats[i]. temps_moyen,
                   ecart_type);
        }
    }
    
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
}

/**
 * @brief Affiche un résumé comparatif des algorithmes
 * @param fichier_csv Nom du fichier CSV contenant les résultats
 */
void afficher_resume_comparatif() {
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║                    RÉSUMÉ COMPARATIF DES ALGORITHMES                  ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Algorithme           │ Complexité  │ Stabilité │ Espace             ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Tri à bulles         │ O(n²)       │ Stable    │ O(1)               ║\n");
    printf("║ Tri bulles optimisé  │ O(n²)       │ Stable    │ O(1)               ║\n");
    printf("║ Tri Gnome            │ O(n²)       │ Stable    │ O(1)               ║\n");
    printf("║ Tri par base         │ O(k·n)      │ Stable    │ O(n)               ║\n");
    printf("║ Tri rapide           │ O(n log n)  │ Instable  │ O(log n)           ║\n");
    printf("║ Tri par tas          │ O(n log n)  │ Instable  │ O(1)               ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════╣\n");
    printf("║ OBSERVATIONS:                                                         ║\n");
    printf("║ • Les algorithmes O(n²) sont inefficaces pour les grands tableaux    ║\n");
    printf("║ • Le tri rapide est généralement le plus rapide en pratique          ║\n");
    printf("║ • Le tri par tas offre les meilleures garanties (toujours O(n log n))║\n");
    printf("║ • Le tri par base est efficace pour les entiers de petite taille     ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
}

/* ===================================== */
/* Programme principal                   */
/* ===================================== */

int main(void) {
    // Initialisation du générateur aléatoire
    srand(time(NULL));
    
    // Noms des algorithmes
    const char *noms_algos[] = {
        "Tri à bulles",
        "Tri bulles optimisé",
        "Tri Gnome",
        "Tri par base",
        "Tri rapide",
        "Tri par tas"
    };
    const int NB_ALGOS = 6;
    
    // Ouverture du fichier CSV
    FILE *fichier_csv = fopen(FICHIER_RESULTATS, "w");
    if (fichier_csv == NULL) {
        printf("ERREUR: Impossible de créer le fichier de résultats.\n");
        printf("Assurez-vous que le dossier 'results/' existe.\n");
        return 1;
    }
    
    // Initialiser le fichier CSV
    initialiser_csv(fichier_csv);
    
    // Affichage de l'en-tête
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════════╗\n");
    printf("║          BENCHMARK DES ALGORITHMES DE TRI - Analyse comparative      ║\n");
    printf("╠═══════════════════════════════════════════════════════════════════════╣\n");
    printf("║ Configuration:                                                         ║\n");
    printf("║   • Nombre d'itérations par test: %-3d                               ║\n", NB_ITERATIONS);
    printf("║   • Valeur maximale des entiers: %-6d                             ║\n", MAX_VALUE);
    printf("║   • Tailles de tableaux testées: %d valeurs                          ║\n", NB_TAILLES);
    printf("║   • Fichier de sortie: %-45s ║\n", FICHIER_RESULTATS);
    printf("╚═══════════════════════════════════════════════════════════════════════╝\n");
    
    int progression_totale = 0;
    int nb_tests_total = NB_TAILLES * NB_ALGOS;
    
    // Boucle sur les différentes tailles
    for (int t = 0; t < NB_TAILLES; t++) {
        int taille = TAILLES[t];
        
        // Générer un tableau aléatoire
        int *tableau_original = (int *)malloc(taille * sizeof(int));
        if (tableau_original == NULL) {
            printf("\nERREUR: Allocation mémoire échouée pour n=%d\n", taille);
            continue;
        }
        generer_tableau_aleatoire(tableau_original, taille, MAX_VALUE);
        
        // Tableau pour stocker les résultats
        ResultatTri resultats[NB_ALGOS];
        
        // Tester chaque algorithme
        for (int algo = 0; algo < NB_ALGOS; algo++) {
            resultats[algo].nom = noms_algos[algo];
            
            // Afficher la progression
            progression_totale = ((t * NB_ALGOS + algo + 1) * 100) / nb_tests_total;
            afficher_progression(progression_totale);
            
            // Pour les algorithmes O(n²), limiter la taille max
            if ((algo == 0 || algo == 1 || algo == 2) && taille > 10000) {
                resultats[algo].succes = 0;
                resultats[algo].temps_moyen = -1.0;
                continue;
            }
            
            // Effectuer le benchmark
            benchmark_algorithme(tableau_original, taille, algo, &resultats[algo]);
            
            // Sauvegarder dans le CSV
            ajouter_resultat_csv(fichier_csv, taille, &resultats[algo]);
        }
        
        // Afficher les résultats pour cette taille
        afficher_resultats(taille, resultats, NB_ALGOS);
        
        // Libérer la mémoire
        free(tableau_original);
    }
    
    printf("\n");
    afficher_progression(100);
    printf("\n");
    
    // Fermer le fichier CSV
    fclose(fichier_csv);
    
    // Afficher le résumé comparatif
    afficher_resume_comparatif();
    
    printf("\n✓ Benchmark terminé avec succès!\n");
    printf("✓ Résultats sauvegardés dans:  %s\n\n", FICHIER_RESULTATS);
    printf("Pour visualiser les graphes, vous pouvez utiliser Python avec:\n");
    printf("  • pandas pour lire le CSV\n");
    printf("  • matplotlib ou seaborn pour tracer les courbes\n\n");
    
    return 0;
}