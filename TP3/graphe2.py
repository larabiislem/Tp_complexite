import pandas as pd
import matplotlib.pyplot as plt

# Lire les données
df = pd.read_csv('resultats_sous_matrice.csv')

# Créer la figure
plt.figure(figsize=(14, 8), dpi=100)

# Couleurs pour chaque n1
colors = {2: '#e74c3c', 3: '#3498db', 4: '#2ecc71'}
markers_mat1 = 'o'
markers_mat2 = 's'

# Tracer les courbes pour sousMat1 et sousMat2
for n1 in sorted(df['n1'].unique()):
    data = df[df['n1'] == n1]
    
    # Courbe sousMat1 (ligne continue)
    plt.plot(data['n'], data['Temps_sousMat1'], 
             marker=markers_mat1, 
             markersize=10, 
             linewidth=3,
             color=colors[n1], 
             label=f'sousMat1 (n1={n1})',
             linestyle='-',
             markeredgecolor='white',
             markeredgewidth=2,
             alpha=0.9)
    
    # Courbe sousMat2 (ligne pointillée)
    plt.plot(data['n'], data['Temps_sousMat2'], 
             marker=markers_mat2, 
             markersize=10, 
             linewidth=3,
             color=colors[n1], 
             label=f'sousMat2 (n1={n1})',
             linestyle='--',
             markeredgecolor='white',
             markeredgewidth=2,
             alpha=0.7)

# Configuration du graphique
plt.xlabel('Taille de la matrice (n)', fontsize=14, fontweight='bold', color='#2C3E50')
plt.ylabel('Temps d\'exécution (secondes)', fontsize=14, fontweight='bold', color='#2C3E50')
plt.title('Comparaison des Performances:  sousMat1 vs sousMat2\n(Lignes continues = sousMat1, Lignes pointillées = sousMat2)', 
          fontsize=16, fontweight='bold', color='#2C3E50', pad=20)

# Légende
plt.legend(fontsize=11, loc='upper left', framealpha=0.95, shadow=True, ncol=2)

# Grille
plt.grid(True, alpha=0.3, linestyle='--', linewidth=0.8)

# Couleur de fond
ax = plt.gca()
ax.set_facecolor('#F8F9FA')
plt.gcf().patch.set_facecolor('white')

# Ajustement
plt.tight_layout()

# Sauvegarder et afficher
plt.savefig('comparaison_sous_matrices_courbes.png', dpi=300, bbox_inches='tight')
plt.show()

print("✓ Graphique créé avec succès!")
print("✓ Fichier sauvegardé: comparaison_sous_matrices_courbes.png")