#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

// ==================== PARTIE A: Recherche d'un élément ====================

bool rechElets_TabNonTries(int T[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] == x)
        {
            return true;
        }
    }
    return false;
}

bool rechElets_TabTries(int T[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i] == x)
        {
            return true;
        }
        else if (T[i] > x)
        {
            return false;
        }
    }
    return false;
}

bool rechElets_Dicho(int T[], int n, int x)
{
    int debut = 0;
    int fin = n - 1;

    while (debut <= fin)
    {
        int milieu = (debut + fin) / 2;

        if (T[milieu] == x)
        {
            return true;
        }
        else if (x < T[milieu])
        {
            fin = milieu - 1;
        }
        else
        {
            debut = milieu + 1;
        }
    }

    return false;
}

// ==================== PARTIE B: Max et Min ====================

void MaxEtMinA(int T[], int n, int *min, int *max)
{
    *min = T[0];
    for (int i = 1; i < n; i++)
    {
        if (T[i] < *min)
        {
            *min = T[i];
        }
    }

    *max = T[0];
    for (int i = 1; i < n; i++)
    {
        if (T[i] > *max)
        {
            *max = T[i];
        }
    }
}

// Version avec compteur de comparaisons
void MaxEtMinA_Count(int T[], int n, int *min, int *max, int *comparisons)
{
    *comparisons = 0;
    *min = T[0];
    *max = T[0];

    for (int i = 1; i < n; i++)
    {
        (*comparisons)++;
        if (T[i] < *min)
        {
            *min = T[i];
        }
    }

    for (int i = 1; i < n; i++)
    {
        (*comparisons)++;
        if (T[i] > *max)
        {
            *max = T[i];
        }
    }
}

void MaxEtMinB(int T[], int n, int *min, int *max)
{

    for (int i = 0; i < n - 1; i += 2)
    {
        if (T[i] > T[i + 1])
        {
            int tmp = T[i];
            T[i] = T[i + 1];
            T[i + 1] = tmp;
        }
    }

    *min = T[0];
    for (int i = 2; i < n; i += 2)
    {
        if (T[i] < *min)
        {
            *min = T[i];
        }
    }

    *max = T[1];
    for (int i = 3; i < n; i += 2)
    {
        if (T[i] > *max)
        {
            *max = T[i];
        }
    }

    if (n % 2 != 0)
    {
        int dernier = T[n - 1];
        if (dernier < *min)
        {
            *min = dernier;
        }
        else if (dernier > *max)
        {
            *max = dernier;
        }
    }
}

// Version avec compteur de comparaisons
void MaxEtMinB_Count(int T[], int n, int *min, int *max, int *comparisons)
{
    *comparisons = 0;

    // Phase 1: Comparer par paires
    for (int i = 0; i < n - 1; i += 2)
    {
        (*comparisons)++;
        if (T[i] > T[i + 1])
        {
            int tmp = T[i];
            T[i] = T[i + 1];
            T[i + 1] = tmp;
        }
    }

    // Phase 2: Chercher le min parmi les éléments pairs (les plus petits)
    *min = T[0];
    for (int i = 2; i < n; i += 2)
    {
        (*comparisons)++;
        if (T[i] < *min)
        {
            *min = T[i];
        }
    }

    // Phase 3: Chercher le max parmi les éléments impairs (les plus grands)
    *max = T[1];
    for (int i = 3; i < n; i += 2)
    {
        (*comparisons)++;
        if (T[i] > *max)
        {
            *max = T[i];
        }
    }

    // Gérer le dernier élément si n est impair
    if (n % 2 != 0)
    {
        int dernier = T[n - 1];
        (*comparisons)++;
        if (dernier < *min)
        {
            *min = dernier;
        }
        else
        {
            (*comparisons)++;
            if (dernier > *max)
            {
                *max = dernier;
            }
        }
    }
}

// ==================== Fonctions Utilitaires ====================

void remplirTableauAleatoire(int T[], int n)
{
    for (int i = 0; i < n; i++)
    {
        T[i] = rand() % (n * 10);
    }
}

// Remplir directement un tableau trié (pour éviter le tri)
void remplirTableauTrie(int T[], int n)
{
    T[0] = rand() % 10;
    for (int i = 1; i < n; i++)
    {
        T[i] = T[i - 1] + (rand() % 10) + 1; // valeurs croissantes
    }
}

void copierTableau(int src[], int dest[], int n)
{
    for (int i = 0; i < n; i++)
    {
        dest[i] = src[i];
    }
}
