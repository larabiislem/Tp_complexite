import pandas as pd
import matplotlib.pyplot as plt

# Lire le fichier CSV
df = pd. read_csv('resultats.csv', sep=';')

# Configurer le style
plt.style.use('seaborn-v0_8-darkgrid')
colors = ['#FF6B6B', '#4ECDC4', '#45B7D1', '#FFA07A', '#98D8C8', '#F7DC6F']

# 1. GRAPHIQUES INDIVIDUELS pour chaque algorithme
print("Génération des graphiques individuels...")

algos = df. columns[1:]  # Tous sauf 'Taille(n)'

for i, algo in enumerate(algos):
    plt.figure(figsize=(10, 6))

    # Filtrer les valeurs non-erreur
    data = df[['Taille(n)', algo]].copy()
    data = data[data[algo] != 'ERREUR']
    data[algo] = pd.to_numeric(data[algo])

    plt.plot(data['Taille(n)'], data[algo],
             marker='o', linewidth=2, markersize=8,
             color=colors[i % len(colors)], label=algo)

    plt.xlabel('Taille du tableau (n)', fontsize=12, fontweight='bold')
    plt.ylabel('Temps d\'exécution (µs)', fontsize=12, fontweight='bold')
    plt.title(f'Performance de {algo}', fontsize=14, fontweight='bold')
    plt.grid(True, alpha=0.3)
    plt.legend(fontsize=10)

    # Sauvegarder
    filename = f'graphique_{algo}.png'
    plt.savefig(filename, dpi=300, bbox_inches='tight')
    print(f"  ✓ {filename}")
    plt.close()

# 2. GRAPHIQUE GLOBAL (tous les algorithmes)
print("\nGénération du graphique global...")

plt.figure(figsize=(14, 8))

for i, algo in enumerate(algos):
    data = df[['Taille(n)', algo]].copy()
    data = data[data[algo] != 'ERREUR']

    if not data.empty:
        data[algo] = pd.to_numeric(data[algo])
        plt.plot(data['Taille(n)'], data[algo],
                 marker='o', linewidth=2, markersize=6,
                 color=colors[i % len(colors)], label=algo)

plt.xlabel('Taille du tableau (n)', fontsize=13, fontweight='bold')
plt.ylabel('Temps d\'exécution (µs)', fontsize=13, fontweight='bold')
plt.title('Comparaison des Algorithmes de Tri', fontsize=16, fontweight='bold')
plt.grid(True, alpha=0.3)
plt.legend(fontsize=11, loc='upper left')
plt.tight_layout()

plt.savefig('graphique_global.png', dpi=300, bbox_inches='tight')
print("  ✓ graphique_global.png")

# 3. GRAPHIQUE GLOBAL avec échelle logarithmique (pour mieux voir les différences)
print("\nGénération du graphique global (échelle log)...")

plt.figure(figsize=(14, 8))

for i, algo in enumerate(algos):
    data = df[['Taille(n)', algo]].copy()
    data = data[data[algo] != 'ERREUR']

    if not data.empty:
        data[algo] = pd. to_numeric(data[algo])
        plt.plot(data['Taille(n)'], data[algo],
                 marker='o', linewidth=2, markersize=6,
                 color=colors[i % len(colors)], label=algo)

plt.xlabel('Taille du tableau (n)', fontsize=13, fontweight='bold')
plt.ylabel('Temps d\'exécution (µs) - échelle log', fontsize=13, fontweight='bold')
plt.title('Comparaison des Algorithmes de Tri (Échelle Logarithmique)',
          fontsize=16, fontweight='bold')
plt.yscale('log')
plt.grid(True, alpha=0.3, which='both')
plt.legend(fontsize=11, loc='upper left')
plt.tight_layout()

plt.savefig('graphique_global_log.png', dpi=300, bbox_inches='tight')
print("  ✓ graphique_global_log.png")

# 4. TABLEAU RÉCAPITULATIF
print("\n=== STATISTIQUES ===")
print(df.to_string(index=False))

print("\n✓ Tous les graphiques ont été générés avec succès!")
print("\nFichiers créés:")
for algo in algos:
    print(f"  - graphique_{algo}.png")
print("  - graphique_global.png")
print("  - graphique_global_log.png")