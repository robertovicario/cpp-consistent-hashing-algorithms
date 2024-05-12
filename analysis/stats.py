"""
@author Roberto Vicario
"""

import pandas as pd

"""
TODO: Update the 'benchmark' variable to choose the benchmark to visualize.
"""

data = pd.read_csv("analysis/data/results.csv")

# (1)
benchmark = data[data['benchmark'] == 'balance']

results = benchmark.groupby('algorithm')['mean'].mean()
print(results)