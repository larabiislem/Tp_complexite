import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# ========== PARTIE A: Histogramme des temps de recherche (Pire cas) ==========

# Lecture des données de recherche
df_recherche = pd.read_csv('resultats_recherche.csv')

# Graphe 1: Histogramme comparaison des 3 méthodes de recherche (pire cas)
plt.figure(figsize=(14, 7))

x = np.arange(len(df_recherche['n']))
width = 0.25

bars1 = plt.bar(x - width, df_recherche['EletsNonTries_Pire'], width,
                label='Recherche Non Triée (Pire cas)', color='red', edgecolor='black')
bars2 = plt.bar(x, df_recherche['EletsTries_Pire'], width,
                label='Recherche Triée Séquentielle (Pire cas)', color='blue', edgecolor='black')
bars3 = plt.bar(x + width, df_recherche['EletsTriesDicho_Pire'], width,
                label='Recherche Dichotomique (Pire cas)', color='green', edgecolor='black')

plt.xlabel('Taille du tableau (n)', fontsize=12)
plt.ylabel('Temps d\'exécution (µs)', fontsize=12)
plt.title('Comparaison des temps d\'exécution des 3 méthodes de recherche\n(Pire cas)', fontsize=14)
plt.xticks(x, df_recherche['n'].astype(str), rotation=45)
plt.legend(fontsize=10)
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('graphe_recherche_pire_cas.png', dpi=150)
plt.show()

print("Graphe 'graphe_recherche_pire_cas.png' sauvegardé!")

# Graphe spécifique TP: Variations de T(N) des 3 fonctions (tableau trié, pire cas) - PILIERS
plt.figure(figsize=(14, 7))

x = np.arange(len(df_recherche['n']))
width = 0.25

bars1 = plt.bar(x - width, df_recherche['EletsNonTries_Pire'], width,
                label='Recherche Séquentielle Non Triée (Pire cas)', color='red', edgecolor='black')
bars2 = plt.bar(x, df_recherche['EletsTries_Pire'], width,
                label='Recherche Séquentielle Triée (Pire cas)', color='blue', edgecolor='black')
bars3 = plt.bar(x + width, df_recherche['EletsTriesDicho_Pire'], width,
                label='Recherche Dichotomique (Pire cas)', color='green', edgecolor='black')

plt.xlabel('Taille du tableau n', fontsize=12)
plt.ylabel('Temps d\'exécution T(N) en µs', fontsize=12)
plt.title('Variations du temps d\'exécution T(N) des 3 fonctions de recherche\n(Tableau trié - Pire cas)', fontsize=14)
plt.xticks(x, df_recherche['n'].astype(str), rotation=45)
plt.legend(fontsize=10, loc='upper left')
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('graphe_variations_TN_pire_cas.png', dpi=150)
plt.show()

print("Graphe 'graphe_variations_TN_pire_cas.png' sauvegardé!")

# Graphe 2: Histogramme comparaison meilleur cas vs pire cas
fig, axes = plt.subplots(1, 3, figsize=(16, 5))

x = np.arange(len(df_recherche['n']))
width = 0.35

# Non Trié
axes[0].bar(x - width/2, df_recherche['EletsNonTries_Meilleur'], width,
            label='Meilleur cas', color='green', edgecolor='black')
axes[0].bar(x + width/2, df_recherche['EletsNonTries_Pire'], width,
            label='Pire cas', color='red', edgecolor='black')
axes[0].set_xlabel('n')
axes[0].set_ylabel('Temps (µs)')
axes[0].set_title('Recherche Non Triée')
axes[0].set_xticks(x)
axes[0].set_xticklabels(df_recherche['n'].astype(str), rotation=45, fontsize=8)
axes[0].legend()
axes[0].grid(True, axis='y', linestyle='--', alpha=0.7)

# Trié Séquentiel
axes[1].bar(x - width/2, df_recherche['EletsTries_Meilleur'], width,
            label='Meilleur cas', color='green', edgecolor='black')
axes[1].bar(x + width/2, df_recherche['EletsTries_Pire'], width,
            label='Pire cas', color='red', edgecolor='black')
axes[1].set_xlabel('n')
axes[1].set_ylabel('Temps (µs)')
axes[1].set_title('Recherche Triée Séquentielle')
axes[1].set_xticks(x)
axes[1].set_xticklabels(df_recherche['n'].astype(str), rotation=45, fontsize=8)
axes[1].legend()
axes[1].grid(True, axis='y', linestyle='--', alpha=0.7)

# Dichotomique
axes[2].bar(x - width/2, df_recherche['EletsTriesDicho_Meilleur'], width,
            label='Meilleur cas', color='green', edgecolor='black')
axes[2].bar(x + width/2, df_recherche['EletsTriesDicho_Pire'], width,
            label='Pire cas', color='red', edgecolor='black')
axes[2].set_xlabel('n')
axes[2].set_ylabel('Temps (µs)')
axes[2].set_title('Recherche Dichotomique')
axes[2].set_xticks(x)
axes[2].set_xticklabels(df_recherche['n'].astype(str), rotation=45, fontsize=8)
axes[2].legend()
axes[2].grid(True, axis='y', linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('graphe_recherche_comparaison.png', dpi=150)
plt.show()

print("Graphe 'graphe_recherche_comparaison.png' sauvegardé!")


# ========== PARTIE B: Histogrammes MaxEtMin ==========

# Lecture des données MaxMin
df_maxmin = pd.read_csv('resultats_maxmin.csv')

# Graphe 3: Histogramme comparaison du nombre de comparaisons
plt.figure(figsize=(12, 6))

x = np.arange(len(df_maxmin['n']))
width = 0.35

bars1 = plt.bar(x - width/2, df_maxmin['MaxEtMinA_comparaisons'], width,
                label='MaxEtMinA: 2(n-1)', color='red', edgecolor='black')
bars2 = plt.bar(x + width/2, df_maxmin['MaxEtMinB_comparaisons'], width,
                label='MaxEtMinB: 3n/2 - 2', color='blue', edgecolor='black')

plt.xlabel('Taille du tableau (n)', fontsize=12)
plt.ylabel('Nombre de comparaisons', fontsize=12)
plt.title('Comparaison du nombre de comparaisons\nMaxEtMinA vs MaxEtMinB', fontsize=14)
plt.xticks(x, df_maxmin['n'].astype(str), rotation=45)
plt.legend(fontsize=10)
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('graphe_maxmin_comparaisons.png', dpi=150)
plt.show()

print("Graphe 'graphe_maxmin_comparaisons.png' sauvegardé!")

# Graphe 4: Histogramme comparaison des temps d'exécution
plt.figure(figsize=(12, 6))

x = np.arange(len(df_maxmin['n']))
width = 0.35

bars1 = plt.bar(x - width/2, df_maxmin['MaxEtMinA_temps(us)'], width,
                label='MaxEtMinA', color='red', edgecolor='black')
bars2 = plt.bar(x + width/2, df_maxmin['MaxEtMinB_temps(us)'], width,
                label='MaxEtMinB', color='blue', edgecolor='black')

plt.xlabel('Taille du tableau (n)', fontsize=12)
plt.ylabel('Temps d\'exécution (µs)', fontsize=12)
plt.title('Comparaison des temps d\'exécution\nMaxEtMinA vs MaxEtMinB', fontsize=14)
plt.xticks(x, df_maxmin['n'].astype(str), rotation=45)
plt.legend(fontsize=10)
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('graphe_maxmin_temps.png', dpi=150)
plt.show()

print("Graphe 'graphe_maxmin_temps.png' sauvegardé!")

# Graphe 5: Gain en pourcentage
plt.figure(figsize=(10, 6))

plt.bar(df_maxmin['n'].astype(str), df_maxmin['Gain(%)'], color='green', alpha=0.7, edgecolor='black')

plt.xlabel('Taille du tableau (n)', fontsize=12)
plt.ylabel('Gain (%)', fontsize=12)
plt.title('Gain en pourcentage de MaxEtMinB par rapport à MaxEtMinA\n(en nombre de comparaisons)', fontsize=14)
plt.ylim(0, 30)
plt.grid(True, axis='y', linestyle='--', alpha=0.7)

# Ajouter les valeurs sur les barres
for i, v in enumerate(df_maxmin['Gain(%)']):
    plt.text(i, v + 0.5, f'{v:.2f}%', ha='center', fontsize=9)

plt.tight_layout()
plt.savefig('graphe_maxmin_gain.png', dpi=150)
plt.show()

print("Graphe 'graphe_maxmin_gain.png' sauvegardé!")

print("\n" + "="*50)
print("Tous les graphes ont été générés avec succès!")
print("="*50)
