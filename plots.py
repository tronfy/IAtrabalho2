import numpy as np
import matplotlib.pyplot as plt
import os

plt.rcParams.update({'font.size': 16})

N = 10
FILE = "result_N=50_P=50_alpha=1.00_lambda=1.00_A={1.00,1.00}_"
RESULTADOS = "resultados_novo"
OUTDIR = "plots"

if not os.path.exists(RESULTADOS): os.makedirs(RESULTADOS)
if not os.path.exists(OUTDIR): os.makedirs(OUTDIR)

def run(results_dir, i):
  os.system(f"./main {results_dir} {i}")


def plot_all():
  for i in range(N):
    data = np.loadtxt(f"{RESULTADOS}/{FILE}{i}.txt")
    plt.plot(data,label=f"Simulação {i}")

  plt.legend()
  plt.xscale("log")
  plt.yscale("log")
  plt.xlabel("Número de iterações")
  plt.ylabel("Função objetivo")
  plt.suptitle("Prioridade para o ótimo individual")
  
  plt.savefig(f"{OUTDIR}/{FILE}.png")

for i in range(1, N):
  run(RESULTADOS, i)

plot_all()