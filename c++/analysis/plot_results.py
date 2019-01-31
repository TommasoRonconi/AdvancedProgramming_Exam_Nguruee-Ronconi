import matplotlib.pyplot as plt
import numpy as np

filein = "../output/test_unordered.dat"

ss, minTu, Tu, maxTu, minTo, To, maxTo, minTm, Tm, maxTm = np.genfromtxt(filein, unpack=True)

fig = plt.figure( figsize=(12,8) )
ax = fig.add_subplot( 1, 1, 1 )

ax.set_title("find() (random input)", fontsize=22)
ax.tick_params(axis='both', labelsize=18)
ax.set_xscale('log')
ax.set_xlabel("$N_\\mathrm{nodes}$", fontsize=18)
ax.set_yscale('log')
ax.set_ylabel("time for the answer [nsec]", fontsize=18)

ax.plot(ss, 1.e-4*To[0]*np.log10(ss)/np.log10(ss[0]), '--k', alpha=0.7, label="$t \\propto\\ \\log N$")
ax.plot(ss, 1.e-4*Tu, lw=2., label="Tree unbalanced")
ax.fill_between(ss, 1.e-4*minTu, 1.e-4*maxTu, alpha=0.4)
ax.plot(ss, 1.e-4*To, lw=2., label="Tree balanced")
ax.fill_between(ss, 1.e-4*minTo, 1.e-4*maxTo, alpha=0.4)
ax.plot(ss, 1.e-4*Tm, lw=2., label="std::map")
ax.fill_between(ss, 1.e-4*minTm, 1.e-4*maxTm, alpha=0.4)
ax.legend(loc='upper left', fontsize=18, ncol=2)
plt.savefig("../output/plot_random.png", bbox_inches='tight')
plt.show()
