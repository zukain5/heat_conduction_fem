import numpy as np


def main():
    # 基底の読み込み
    with open('PARAMETERS') as f:
        info_l = f.readlines()
    basis_count = int(info_l[2])
    n = int(info_l[0])

    with open('02_Vk') as f:
        basis_l = f.readlines()

    basis = np.matrix(np.array(basis_l, dtype=float).reshape([basis_count, n]))
    multiplier = (((basis.T * basis) + 0.00001 * np.eye(n)) ** -1) * basis.T

    ys = np.loadtxt('OUTPUTALL.csv', delimiter=',')

    for y in ys:
        y = np.matrix(y)
        a = multiplier * y
        error = y - basis * a
        error_value = np.linalg.norm(np.array(error))
        print(error_value)


if __name__ == '__main__':
    main()
