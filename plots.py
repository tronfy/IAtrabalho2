import numpy as np
import matplotlib.pyplot as plt
import os
from random import randint, seed
from time import time

# plt.rcParams.update({"font.size": 16})

NSIMS = 100
NPRESAS = 30  # 1 <= N <= 99
NPREDS = 10  # 1 <= P <= 99
ALPHA = 5.0
LAMBDA = 3.0
A = [1, 1]
FILE = f"result_N={NPRESAS:2.0f}_P={NPREDS:02.0f}_alpha={ALPHA:3.2f}_lambda={LAMBDA:3.2f}_A={A[0]:3.2f},{A[1]:3.2f}_"
RESULTADOS = "res"
OUTDIR = "plots"

if not os.path.exists(RESULTADOS):
    os.makedirs(RESULTADOS)
if not os.path.exists(OUTDIR):
    os.makedirs(OUTDIR)

seed(time())


def run(results_dir, i):
    seed = randint(0, 100000)
    print(
        f"./main {results_dir} {i} {seed} {NPRESAS} {NPREDS} {ALPHA} {LAMBDA} {A[0]} {A[1]}"
    )
    os.system(
        f"./main {results_dir} {i} {seed} {NPRESAS} {NPREDS} {ALPHA} {LAMBDA} {A[0]} {A[1]}"
    )


def plot_all():
    plt.figure(figsize=(12, 8))

    for i in range(NSIMS):
        data = np.loadtxt(f"{RESULTADOS}/{FILE}{i+1}.txt")
        plt.plot(data, label=f"Simulação {i}")

    plt.legend()
    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Número de iterações")
    plt.ylabel("Função objetivo")
    plt.suptitle(
        f"Npresas={NPRESAS}, Npreds={NPREDS}, alpha={ALPHA}, lambda={LAMBDA}, A=[{A[0]}, {A[1]}]"
    )

    plt.savefig(f"{OUTDIR}/{FILE}.png")


def plot_mean():
    plt.figure(figsize=(12, 8))

    datum = []
    for i in range(NSIMS):
        data = np.loadtxt(f"{RESULTADOS}/{FILE}{i+1}.txt")
        datum.append(data)

    mean = np.mean(datum, axis=0)
    np.savetxt(f"{OUTDIR}/{FILE}_mean.txt", mean)
    std = np.std(datum, axis=0)

    plt.plot(mean, label=f"Média entre {NSIMS} simulações")
    plt.fill_between(range(len(mean)), mean - std, mean + std, alpha=0.3)

    plt.legend()
    plt.xscale("log")
    plt.yscale("log")
    plt.xlabel("Número de iterações")
    plt.ylabel("Média da Função objetivo")
    plt.suptitle(
        f"Npresas={NPRESAS}, Npreds={NPREDS}, alpha={ALPHA}, lambda={LAMBDA}, A=[{A[0]}, {A[1]}]"
    )

    print(f"{OUTDIR}/{FILE}_mean.png")
    plt.savefig(f"{OUTDIR}/{FILE}_mean.png")


for i in range(NSIMS):
    run(RESULTADOS, i + 1)

plot_all()
plot_mean()
