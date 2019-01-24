import matplotlib.pyplot as plt
import numpy as np

filein = "../output/test_ordered.dat"

ss, minTu, Tu, maxTu, minTo, To, maxTo, minTm, Tm, maxTm = np.genfromtxt(filein, unpack=True)

fig = plt.figure( figsize=(12,8) )
ax = fig.add_subplot( 1, 1, 1 )

ax.set_title("Find $42$ (ordered input)", fontsize=22)
ax.set_xscale('log')
ax.set_xlim([70, 1.4e+5])
ax.set_xlabel("$N_\\mathrm{nodes}$", fontsize=18)
ax.set_xticks([1.e+2, 1.e+3, 1.e+4, 1.e+5])
ax.set_xticklabels(["$10^2$", "$10^3$", "$10^4$", "$10^5$"], fontsize=18)
ax.set_yscale('log')
ax.set_ylim([40.,4000.])
ax.set_ylabel("time for the answer [nsec]", fontsize=18)
ax.set_yticks([100., 1000.])
ax.set_yticklabels(["100", "1000"], fontsize=18)

ax.plot(ss, To[0]*np.log10(ss)/np.log10(ss[0]), '--k', alpha=0.7, label="$t \\propto\\ \\log N$")
ax.plot(ss, Tu, lw=2., label="Tree unbalanced")
ax.fill_between(ss, minTu, maxTu, alpha=0.4)
ax.plot(ss, To, lw=2., label="Tree balanced")
ax.fill_between(ss, minTo, maxTo, alpha=0.4)
ax.plot(ss, Tm, lw=2., label="std::map")
ax.fill_between(ss, minTm, maxTm, alpha=0.4)
ax.legend(loc='lower right', fontsize=18, ncol=2)
plt.savefig("../output/plot_ordered.png", bbox_inches='tight')
plt.show()
