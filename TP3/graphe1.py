import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('temps_multiplication - temps_multiplication.csv.csv')

# Print to see what we're working with
print("Column names found:", df.columns.tolist())
print("\nFirst few rows:")
print(df.head())

# Use iloc to access by position (most reliable method)
n_values = df.iloc[:, 0].values  # First column
temps_values = df.iloc[:, 1].values  # Second column

print(f"\nn values: {n_values}")
print(f"temps values: {temps_values}")

# Create the plot
plt.figure(figsize=(12, 7), dpi=100)

# Plot the curve
plt.plot(n_values, temps_values, 
         marker='o', 
         markersize=10, 
         linewidth=3, 
         color='#3498db',
         markerfacecolor='#e74c3c',
         markeredgecolor='white',
         markeredgewidth=2.5,
         label='Temps d\'exécution')

# Fill area under the curve
plt.fill_between(n_values, temps_values, alpha=0.2, color='#3498db')

# Labels and title
plt.xlabel('Taille de la matrice (n)', fontsize=14, fontweight='bold')
plt.ylabel('Temps d\'exécution (secondes)', fontsize=14, fontweight='bold')
plt.title('Variation du Temps d\'Exécution en Fonction de n', 
          fontsize=16, fontweight='bold', pad=20)

# Grid
plt.grid(True, alpha=0.3, linestyle='--', linewidth=0.8)

# Legend
plt.legend(fontsize=12, loc='upper left', framealpha=0.9, shadow=True)

# Background color
ax = plt.gca()
ax.set_facecolor('#f8f9fa')

# Add value labels on points
for i in range(len(n_values)):
    plt.annotate(f'{temps_values[i]:.2f}s', 
                xy=(n_values[i], temps_values[i]),
                xytext=(10, 10),
                textcoords='offset points',
                fontsize=9,
                bbox=dict(boxstyle='round,pad=0.5', 
                         facecolor='yellow', 
                         alpha=0.7),
                arrowprops=dict(arrowstyle='->', 
                              color='gray', 
                              lw=1))

# Adjust layout and save
plt.tight_layout()
plt.savefig('temps_execution_graph.png', dpi=300, bbox_inches='tight')
plt.show()

print("\n✓ Graphique créé avec succès!")
print("✓ Fichier sauvegardé:  temps_execution_graph.png")