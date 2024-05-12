"""
@author Roberto Vicario
"""

import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

"""
TODO:
1. Update the 'benchmark' variable to choose the benchmark to visualize.
2. Adjust the y-axis label by modifying the 'plt.ylabel'.
"""

df = pd.read_csv('analysis/data/results.csv')

# (1)
benchmark = 'balance'

filtered_df = df[df['benchmark'] == benchmark]
sns.set_style("whitegrid")
plt.figure(figsize=(8, 6))
sns.barplot(data=filtered_df, x='init_nodes', y='mean', hue='algorithm', palette='viridis')
plt.xlabel('Init Nodes')

# (2)
plt.ylabel('Balance')

plt.legend(title='Algorithm')
plt.tight_layout()
plt.show()