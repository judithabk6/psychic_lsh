names = ['neib_5_hash_5.npy', 'neib_15_hash_5.npy', "neib_30_hash_5.npy", "neib_5_hash_12.npy", "neib_15_hash_12.npy", "neib_30_hash_12.npy"]

import numpy as np
import matplotlib.pyplot as plt

import colorsys

N = len(names)

cm = plt.get_cmap('gist_rainbow')

# or if you really want a generator:
cgen = [cm(1.*i/N) for i in range(N)]

x = np.log2([0, 1, 2, 3, 5, 8, 10, 16, 20, 40, 60, 100])
for i,n in enumerate(names):
    a = np.load(n)
    y = np.mean(a,0)
    yerr = np.std(a,0)
    plt.figure(1)
    plt.errorbar(x, y, yerr=yerr, label=n, color=cgen[i], lw=2)
plt.legend(loc=2)
plt.savefig('merde.pdf')