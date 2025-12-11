#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <stdbool.h>

// Partie A: Recherche d'un élément
bool rechElets_TabNonTries(int T[], int n, int x);
bool rechElets_TabTries(int T[], int n, int x);
bool rechElets_Dicho(int T[], int n, int x);

// Partie B: Recherche du maximum et du minimum
void MaxEtMinA(int T[], int n, int *min, int *max);
void MaxEtMinB(int T[], int n, int *min, int *max);

// Versions avec compteur de comparaisons
void MaxEtMinA_Count(int T[], int n, int *min, int *max, int *comparisons);
void MaxEtMinB_Count(int T[], int n, int *min, int *max, int *comparisons);

// Fonctions utilitaires
void remplirTableauAleatoire(int T[], int n);
void remplirTableauTrie(int T[], int n);
void copierTableau(int src[], int dest[], int n);

#endif
