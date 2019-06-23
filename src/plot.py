import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from matplotlib import colors
from pprint import pprint
from matplotlib.ticker import LinearLocator, FormatStrFormatter
from mpl_toolkits.mplot3d import Axes3D  # noqa: F401 unused import

def load_data():
    f = open('teste.txt', 'r')
    data = f.readlines()
    fdata = []
    for q in data:
        fdata.append(float(q[:-1]))
    arr = np.array(fdata)
    arr = arr.reshape((41, 81))
    # print(arr)
    # print(arr.shape)
    # print(arr)
    return arr
    
def load_data2():
    f = open('ground.txt', 'r')
    data = f.readlines()
    fdata = []
    for q in data:
        fdata.append(float(q[:-1]))
    arr = np.array(fdata)
    arr = arr.reshape((11, 21))
    # print(arr)
    # print(arr.shape)
    # print(arr)
    return arr

def main3():
    data = load_data()

    xs = range(0, 81)
    ys = range(0, 41)

    xs_labels = []
    ys_labels = []
    for i in xs:
        xs_labels.append(i * 0.125)
        ys_labels.append(i * 0.125)

    print(xs_labels)
    print(ys_labels)

    fig, ax = plt.subplots()
    im = ax.imshow(data)

    # We want to show all ticks...
    ax.set_xticks(np.arange(len(xs)))
    ax.set_yticks(np.arange(len(ys)))
    # ... and label them with the respective list entries
    ax.set_xticklabels(xs_labels)
    ax.set_yticklabels(ys_labels)

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
            rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.
    # for i in range(len(ys)):
    #     for j in range(len(xs)):
    #         text = ax.text(j, i, data[i, j],
    #                     ha="center", va="center", color="w")

    ax.set_title("Calculado")
    fig.tight_layout()
    plt.show()

def main_3d():
    fig = plt.figure()
    ax = fig.gca(projection='3d')

    # Make data.
    X = np.arange(0, 10.125, 0.125)
    Y = np.arange(0, 5.125, 0.125)
    X, Y = np.meshgrid(X, Y)

    R = np.sqrt(X**2 + Y**2)
    Z = np.sin(R)
    Q = load_data()
    print(Z.shape)
    print(Q.shape)
 #   exit()

#    Z = load_data2()

    # Plot the surface.
    surf = ax.plot_surface(X, Y, Q, cmap=cm.jet,
                        linewidth=0, antialiased=False)

    # Customize the z axis.
    # ax.set_zlim(-1.01, 1.01)
    # ax.zaxis.set_major_locator(LinearLocator(10))
    # ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

    # Add a color bar which maps values to colors.
    fig.colorbar(surf, shrink=0.5, aspect=5)

    plt.show()

if __name__ == '__main__':
    main3()
    main_3d()