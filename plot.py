import matplotlib
import pandas as pd
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

data = pd.read_csv("data.csv")
heads = list(data.columns)

x = [i+1 for i in range(int(heads[1]))]
figure, axis = plt.subplots(2,1)

axis[0].plot(x, list(data.iloc[:int(heads[1]), 0]))
axis[0].set_title(f"Tid - {heads[0]}")
axis[0].set_xlabel("Input size")
axis[0].set_ylabel("Time (ms)")

axis[1].plot(x, list(data.iloc[:int(heads[1]), 1]))
axis[1].set_title(f"Memory - {heads[0]}")
axis[1].set_xlabel("Input size")
axis[1].set_ylabel("Memory (kb)")
plt.show()

