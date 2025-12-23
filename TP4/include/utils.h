#ifndef UTILS_H
#define UTILS_H

#include <time.h>

/**
 * @file utils. h
 * @brief Fonctions utilitaires pour les benchmarks
 */

/**
 * @brief Génère un tableau d'entiers aléatoires
 * @param tableau Tableau à remplir
 * @param taille Taille du tableau
 * @param max_value Valeur maximale des entiers générés
 */
void generer_tableau_aleatoire(int tableau[], int taille, int max_value);

/**
 * @brief Copie un tableau source dans un tableau destination
 * @param source Tableau source
 * @param destination Tableau destination
 * @param taille Taille des tableaux
 */
void copier_tableau(int source[], int destination[], int taille);

/**
 * @brief Vérifie si un tableau est trié
 * @param tableau Tableau à vérifier
 * @param taille Taille du tableau
 * @return 1 si trié, 0 sinon
 */
int verifier_tri(int tableau[], int taille);

/**
 * @brief Affiche un tableau
 * @param tableau Tableau à afficher
 * @param taille Taille du tableau
 */
void afficher_tableau(int tableau[], int taille);

/**
 * @brief Calcule la différence de temps en millisecondes
 * @param debut Temps de début
 * @param fin Temps de fin
 * @return Différence en millisecondes
 */
double temps_ecoule_ms(clock_t debut, clock_t fin);

#endif /* UTILS_H */