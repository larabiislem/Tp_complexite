#include <stdbool.h>

bool rechElets_TabNonTries(int T[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (T[i] == x) {
            return true;
        }
    }
    return false;
}


bool rechElets_TabTries(int T[], int n, int x) {
    for (int i = 0; i < n; i++) {
        if (T[i] == x) {
            return true;
        } else if (T[i] > x) {
            return false;  
        }
    }
    return false;
}

bool rechElets_Dicho(int T[], int n, int x) {
    int debut = 0;
    int fin = n - 1;

    while (debut <= fin) {
        int milieu = (debut + fin) / 2;

        if (T[milieu] == x) {
            return true;
        } else if (x < T[milieu]) {
            fin = milieu - 1;
        } else {
            debut = milieu + 1;
        }
    }

    return false;
}



void MaxEtMinA(int T[], int n, int *min, int *max) {
    *min = T[0];
    for (int i = 1; i < n; i++) {
        if (T[i] < *min) {
            *min = T[i];
        }
    }

    *max = T[0];
    for (int i = 1; i < n; i++) {
        if (T[i] > *max) {
            *max = T[i];
        }
    }
}


#include <stdio.h>

void MaxEtMinB(int T[], int n, int *min, int *max) {

    for (int i = 0; i < n - 1; i += 2) {
        if (T[i] > T[i+1]) {
            int tmp = T[i];
            T[i] = T[i+1];
            T[i+1] = tmp;
        }
    }

    *min = T[0];
    for (int i = 2; i < n; i += 2) {
        if (T[i] < *min) {
            *min = T[i];
        }
    }


    *max = T[1];
    for (int i = 3; i < n; i += 2) {
        if (T[i] > *max) {
            *max = T[i];
        }
    }

    if (n % 2 != 0) {
        int dernier = T[n-1];
        if (dernier < *min) {
            *min = dernier;
        } else if (dernier > *max) {
            *max = dernier;
        }
    }
}
