names = ["neib_15_hash_12.npy", "neib_15_hash_5.npy",    "neib_30_hash_40.npy",   "neib_50_hash_20.npy",   "neib_5_hash_5.npy" , "neib_15_hash_20.npy",  "neib_30_hash_12.npy",  "neib_30_hash_5.npy" , "neib_5_hash_12.npy"  , "neib_15_hash_40.npy" ,  "neib_30_hash_20.npy",   "neib_50_hash_12.npy",   "neib_5_hash_20.npy" , "fergus.mat"  ]

import numpy as np
import matplotlib.pyplot as plt

import colorsys

N = len(names)

cm = plt.get_cmap('gist_rainbow')

# or if you really want a generator:
cgen = [cm(1.*i/N) for i in range(N)]

x = np.log2([0, 1, 2, 3, 5, 8, 10, 16, 20, 40, 60, 100])
for i, n in enumerate(names):
    if "npy" in n:
        a = np.load(n)
        zz = 15/a
        a = 15/(zz+1)
    else:
        mat = scipy.io.loadmat(n)
        mm = mat['precision']
        a = mm[:,[0,1,2, 3, 5, 8, 10, 16, 20, 40, 60, 99]]
    y = np.mean(a, 0)
    yerr = np.std(a, 0)
    plt.figure(1, figsize=(11,5), dpi=80, facecolor='w', edgecolor='k')
    plt.subplot(121)
    plt.errorbar(x, y, yerr=yerr, label=n.split('.')[0], color=cgen[i], lw=2)
plt.legend(bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
plt.savefig('/Users/judith/Documents/MVA/graph_valko/psychic_lsh/report/method_comp.pdf')
plt.close()

