import matplotlib.pyplot as plt
import numpy as np
from matplotlib import colors
from pprint import pprint

def main():
    f = open('data.txt', 'r')
    # plt.plot(arr)
    # plt.show()
    print('Plotting...')
    return

def load_data():
    f = open('data.txt', 'r')
    data = f.readlines()
    fdata = []
    for q in data:
        fdata.append(float(q[:-1]))
    arr = np.array(fdata)
    # arr = arr.reshape((11, 21))
    # print(arr)
    print(arr.shape)
    return arr
    

def main2():
    # generate 2 2d grids for the x & y bounds
    y, x = np.meshgrid(np.linspace(0, 10, 100), np.linspace(0, 5, 100))

    z = (1 - x / 2. + x ** 5 + y ** 3) * np.exp(-x ** 2 - y ** 2)
    # q = np.array(z)
    # pprint(q.shape)
    # pprint(z[0])
    # exit()
    # x and y are bounds, so z should be the value *inside* those bounds.
    # Therefore, remove the last value from the z array.
    # z = z[:-1, :-1]
    # z_min, z_max = -np.abs(z).max(), np.abs(z).max()
    z = load_data()
    z_min, z_max = -np.abs(z).max(), np.abs(z).max()

    fig, ax = plt.subplots()

    # c = ax.pcolormesh(x, y, z, cmap='RdBu', vmin=z_min, vmax=z_max)
    ax.set_title('pcolormesh')
    # set the limits of the plot to the limits of the data
    ax.axis([x.min(), x.max(), y.min(), y.max()])
    # fig.colorbar(c, ax=ax)

    plt.show()
    return

if __name__ == '__main__':
    main2()