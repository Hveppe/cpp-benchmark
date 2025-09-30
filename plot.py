import matplotlib
import pandas as pd
matplotlib.use('TkAgg')
import matplotlib.pyplot as plt

size = 1000 # change to be the same as in cpp file
name = "RSA encrypt" # Change name to algortimen that is used 

data = pd.read_csv("data.csv")

x = [i+1 for i in range(size)]
figure, axis = plt.subplots(2,1)

axis[0].plot(x, list(data.iloc[:size, 0]))
axis[0].set_title(f"Tid - {name}")
axis[0].set_xlabel("Input size")
axis[0].set_ylabel("Time (ms)")

axis[1].plot(x, list(data.iloc[:size, 1]))
axis[1].set_title(f"Memory - {name}")
axis[1].set_xlabel("Input size")
axis[1].set_ylabel("Memory (kb)")
plt.show()

