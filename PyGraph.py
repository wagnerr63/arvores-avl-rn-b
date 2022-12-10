import pandas as pd
from matplotlib import pyplot as plt

plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True

columns = ['RN']#, 'AVL', 'B-1', 'B-5', 'B-10']

df = pd.read_csv("casomedio.csv", usecols=columns, sep=";")
#df = pd.read_csv("teste.csv", usecols=columns, sep=";")
df.plot()

plt.xscale("linear")
plt.yscale("log")
plt.show()