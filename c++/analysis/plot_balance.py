import matplotlib.pyplot as plt
import numpy as np

filein = "../output/test_balance.dat"

ss, minT, T, maxT = np.genfromtxt(filein, usecols=(0, 1, 2, 3), unpack=True)

fig = plt.figure( figsize=(12,8) )
ax = fig.add_subplot( 1, 1, 1 )

ax.set_title("Balance time", fontsize=22)
ax.tick_params(axis='both', labelsize=18)
ax.set_xlabel("$N_\\mathrm{nodes}$", fontsize=18)
ax.set_ylabel("balance time [msec]", fontsize=18)

ax.plot(ss, T/1.e+6, lw=2., label="Tree unbalanced")
ax.fill_between(ss, minT/1.e+6, maxT/1.e+6, alpha=0.4)
plt.savefig("../output/plot_balance.png", bbox_inches='tight')
plt.show()
