import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from matplotlib import colors
from pprint import pprint
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import argparse

############### DEFINES ########################

mode = 'Calculado'
# mode = 'Exato'

# Output step = 0.125
# inFname = 'output_SOR_validacao_0.1250_0.1250.txt'

# Output step = 0.25
inFname = 'output_SOR_validacao_0.2500_0.2500.txt'

# Output step = 0.5
# inFname = 'output_SOR_validacao_0.5000_0.5000.txt'

# Dom
x0 = 0
x1 = 10
y0 = 0
y1 = 5

# Steps
hx = 0.25
hy = 0.25

###############################################

def main():
    inputFile = open(inFname, 'r')
    data = inputFile.readlines()
    formData = []
    for q in data:
        formData.append(float(q[:-1]))
    nx = 1 + ((x1-x0)/hx)
    ny = 1 + ((y1-y0)/hy)
    arr = np.array(formData)
    arr = arr.reshape((int(ny), int(nx)))
    plot_2d(arr, nx, ny)
    plot_3d(arr, nx, ny)
    return

def plot_2d(data, nx, ny):
    X = np.arange(x0, x1, hx)
    Y = np.arange(y0, y1, hy)
    fig, ax = plt.subplots()
    im = ax.imshow(data)

    ax.set_xticks(np.arange(len(X)))
    ax.set_yticks(np.arange(len(Y)))

    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
            rotation_mode="anchor")

    ax.set_title(mode)
    fig.tight_layout()
    plt.show()

    return

def plot_3d(data, nx, ny):
    fig = plt.figure()
    ax = fig.gca(projection='3d')
    X = np.arange(x0, x1+hx, hx)
    Y = np.arange(y0, y1+hy, hy)
    X, Y = np.meshgrid(X, Y)
    surf = ax.plot_surface(X, Y, data, cmap=cm.jet, 
                           linewidth=0, antialiased=False)
    fig.colorbar(surf, shrink=0.5, aspect=5)
    plt.show()
    return

if __name__ == '__main__':
    main()