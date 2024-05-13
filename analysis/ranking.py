"""
@author Roberto Vicario
"""

import pandas as pd

"""
TODO: Update the 'benchmark' variable to choose the benchmark to visualize.
"""

df = pd.read_csv('analysis/data/results.csv')

# (1)
benchmark = df[(df['benchmark'] == 'balance') & (df['init_nodes'] == 100000)]

print(benchmark)