#ifndef SORTS_H
#define SORTS_H

/**
 * @file sorts.h
 * @brief Bibliothèque d'algorithmes de tri
 * @author Larabi Islem
 * @date 2025-12-23
 * 
 * Cette bibliothèque implémente différents algorithmes de tri:
 * - Tri à bulles (classique et optimisé)
 * - Tri Gnome
 * - Tri par base (Radix Sort)
 * - Tri rapide (Quick Sort)
 * - Tri par tas (Heap Sort)
 */

/* ===================================== */
/* Fonction utilitaire                   */
/* ===================================== */

/**
 * @brief Échange les valeurs de deux entiers
 * @param a Pointeur vers le premier entier
 * @param b Pointeur vers le second entier
 */
void permuter(int *a, int *b);

/* ===================================== */
/* Algorithmes de tri                    */
/* ===================================== */

/**
 * @brief Tri à bulles classique
 * @param T Tableau à trier
 * @param n Taille du tableau
 * @complexity O(n²) en moyenne et pire cas
 */
void TriBulle(int T[], int n);

/**
 * @brief Tri à bulles optimisé
 * @param T Tableau à trier
 * @param n Taille du tableau
 * @complexity O(n²) en moyenne et pire cas, mais plus rapide en pratique
 */
void TriBulleOpt(int T[], int n);

/**
 * @brief Tri Gnome (Garden Gnome Sort)
 * @param T Tableau à trier
 * @param n Taille du tableau
 * @complexity O(n²) en moyenne et pire cas
 */
void TriGnome(int T[], int n);

/**
 * @brief Tri par base (Radix Sort)
 * @param T Tableau à trier
 * @param n Taille du tableau
 * @param k Nombre de chiffres maximum
 * @complexity O(k*n) où k est le nombre de chiffres
 */
void TriBase(int T[], int n, int k);

/**
 * @brief Tri rapide (Quick Sort)
 * @param tab Tableau à trier
 * @param p Index de début
 * @param r Index de fin
 * @complexity O(n log n) en moyenne, O(n²) au pire
 */
void TriRapide(int tab[], int p, int r);

/**
 * @brief Tri par tas (Heap Sort)
 * @param T Tableau à trier
 * @param n Taille du tableau
 * @complexity O(n log n) dans tous les cas
 */
void TriTas(int T[], int n);

#endif /* SORTS_H */