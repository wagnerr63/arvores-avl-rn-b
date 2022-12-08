import pandas as pd
from matplotlib import pyplot as plt

plt.rcParams["figure.figsize"] = [7.00, 3.50]
plt.rcParams["figure.autolayout"] = True

columns = ['RN Caso Médio', 'RN Pior Caso']#, 'AVL', 'B']

df = pd.read_csv("D:\Programas\Git\\arvores-avl-rn-b\\rubronegra\\teste.csv", usecols=columns, sep=";")
#df = pd.read_csv("teste.csv", usecols=columns, sep=";")
df.plot()

plt.xscale("linear")
plt.yscale("log")
plt.show()