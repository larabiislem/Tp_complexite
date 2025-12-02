#ifndef RECHERCHE_H
#define RECHERCHE_H

#include <stdbool.h>

bool rechElets_TabNonTries(int T[], int n, int x);

bool rechElets_TabTries(int T[], int n, int x);

bool rechElets_Dicho(int T[], int n, int x);

void MaxEtMinA(int T[], int n, int *min, int *max);

void MaxEtMinB(int T[], int n, int *min, int *max);

#endif
