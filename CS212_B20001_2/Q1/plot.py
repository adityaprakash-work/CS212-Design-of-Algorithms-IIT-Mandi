# ---DEPENDENCIES---------------------------------------------------------------
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# ---PLOT GRAHAM SCAN DATA------------------------------------------------------
# Description: Plots the data from the last run of code.cpp stored in data.csv
# data.csv   : x, y, hull

data = pd.read_csv("data.csv")
hull_points = data[data["hull"] != -1].sort_values(["hull"])
hull_points = hull_points._append(hull_points.iloc[0])
palette = {c: "green" for c in hull_points["hull"]}
palette[-1] = "magenta"
sns.scatterplot(x="x", y="y", hue="hull", data=data, palette=palette)
plt.plot(hull_points["x"], hull_points["y"], color="black")
plt.title("Graham Scan")
plt.xlabel("x")
plt.ylabel("y")
plt.legend(["Hull", "Non-Hull"])
plt.savefig("output.png")
plt.show()
