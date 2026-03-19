import pandas as pd
import matplotlib.pyplot as plt

AU = 1.496e11

newton = pd.read_csv("trajectory_newtonian.csv")
modif  = pd.read_csv("trajectory_modified.csv")

earth_n = newton[newton["particle"] == 1]
earth_m = modif[modif["particle"] == 1]

fig, ax = plt.subplots(figsize=(7, 7))
ax.set_aspect("equal")
ax.set_facecolor("#0a0a1a")
fig.patch.set_facecolor("#0a0a1a")

ax.plot(earth_n["x"] / AU, earth_n["y"] / AU,
        color="#4aa8ff", linewidth=1.2, label="Newtonian gravity")
ax.plot(earth_m["x"] / AU, earth_m["y"] / AU,
        color="#ff6b6b", linewidth=1.2, linestyle="--",
        label=f"Modified gravity (α=0.1, λ=1 AU)")
ax.scatter([0], [0], color="#FFD700", s=200, zorder=5, label="Sun")

ax.set_xlabel("x (AU)", color="white")
ax.set_ylabel("y (AU)", color="white")
ax.set_title("Newtonian vs modified gravity", color="white", pad=12)
ax.tick_params(colors="white")
for spine in ax.spines.values():
    spine.set_edgecolor("#333355")
ax.legend(facecolor="#111133", labelcolor="white")

plt.tight_layout()
plt.savefig("orbit_comparison.png", dpi=150, bbox_inches="tight")
plt.show()