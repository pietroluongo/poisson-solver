import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from matplotlib import colors
from pprint import pprint
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import
import argparse

def setStuff():
    global mode, kind, hx, hy, step
    p = 0.125
    mode = 'aprox'
    kind = 'cap'
    hx = p
    hy = p
    step = str(int(p * 10000))

############################ DEFINES ###########################

# mode = 'Exata, passo = 0.25'
title = ''

genOutputsOnly = True

outputFolder = 'imgs'


########## Validacao ##########

# Output step = 0.125
## inFname = 'output_SOR_validacao_0.1250_0.1250.txt'
## inFname = 'elet_SOR_validacao_0.1250_0.1250.txt'

# Output step = 0.25
## inFname = 'output_SOR_validacao_0.2500_0.2500.txt'
## inFname = 'elet_SOR_validacao_0.2500_0.2500.txt'

# Output step = 0.5
## inFname = 'output_SOR_validacao_0.5000_0.5000.txt'
## inFname = 'elet_SOR_validacao_0.5000_0.5000.txt'

# Ground step = 0.5
## inFname = 'ground_SOR_validacao_0.5000_0.5000.txt'
## inFname = 'ground_e_SOR_validacao_0.5000_0.5000.txt'

# Ground step = 0.25
## inFname = 'ground_SOR_validacao_0.2500_0.2500.txt'
## inFname = 'ground_e_SOR_validacao_0.2500_0.2500.txt'

# Ground step = 0.125
## inFname = 'output_SOR_validacao_0.1250_0.1250.txt'
## inFname = 'ground_e_SOR_validacao_0.1250_0.1250.txt'


########### Capacitores ##########

# Output Step = 0.5
## inFname = 'output_SOR_capacitores_0.5000_0.5000.txt'
## inFname = 'elet_SOR_capacitores_0.5000_0.5000.txt'

# Output Step = 0.25
## inFname = 'output_SOR_capacitores_0.2500_0.2500.txt'
## inFname = 'elet_SOR_capacitores_0.2500_0.2500.txt'

# Output Step = 0.125
## inFname = 'output_SOR_capacitores_0.1250_0.1250.txt'
## inFname = 'elet_SOR_capacitores_0.1250_0.1250.txt'

# Dom - MUST MATCH PROBLEM!!!
x0 = 0
x1 = 10
y0 = 0
y1 = 5

mode = 'null'
kind = 'null'
step = '-1'

# Steps - MUST MATCH FILENAME!!!
hx = 0.1250
hy = 0.1250

#################################################################

def main():
    setStuff()
    inputFile = open(inFname, 'r')
    data = inputFile.readlines()
    formData = []
    for q in data:
        formData.append(float(q[:-1]))
    nx = 1 + ((x1-x0)/hx)
    ny = 1 + ((y1-y0)/hy)
    arr = np.array(formData)
    arr = arr.reshape((int(ny), int(nx)))
    plot_contour(arr, nx, ny)
    plot_2d(arr, nx, ny)
    plot_3d(arr, nx, ny)
    return

def plot_contour(data, nx, ny):
    X = np.arange(x0, x1+hx, hx)
    Y = np.arange(y0, y1+hy, hy)
    X, Y = np.meshgrid(X, Y)
    fig, ax = plt.subplots()
    CS = ax.contour(X, Y, data)
    ax.clabel(CS, inline=1, fontsize=10)
    ax.set_title(title)
    # Doesnt make much sense here...
    # fig.colorbar(CS)
    if (genOutputsOnly):
        plt.savefig(outputFolder + '/cont_' + mode + '_' + kind + '_' + step +'.png', dpi=100)
        return
    plt.show()
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
    plt.xticks([])
    plt.yticks([])
    plt.ylabel('Y')
    plt.xlabel('X')
    fig.colorbar(im)
    ax.set_title(title)
    fig.tight_layout()
    if (genOutputsOnly):
        plt.savefig(outputFolder + '/hmap_' + mode + '_' + kind + '_' + step +'.png', dpi=100)
        return
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
    ax.set_title(title)
    if (genOutputsOnly):
        plt.savefig(outputFolder + '/3d_' + mode + '_' + kind + '_' + step +'.png', dpi=100)
        return
    plt.show()
    return

if __name__ == '__main__':
    main()