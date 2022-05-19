import numpy as np
import pandas as pd


def main():
    # 基底の読み込み
    with open('SETTINGS') as f:
        settings_l = f.readlines()
    n = int(settings_l[0].split()[0])+1
    params_count = int(settings_l[2])
    basis_count = int(settings_l[4].split()[1])

    with open('02_Vk') as f:
        basis_l = f.readlines()

    basis = np.matrix(np.array(basis_l, dtype=float).reshape([basis_count, n])).T
    multiplier = (((basis.T * basis) + 0.00001 * np.eye(basis_count)) ** -1) * basis.T

    df = pd.read_csv('OUTPUTALL.csv', index_col=list(range(params_count)))
    ys = df.values

    error_values = []
    for y in ys:
        y = np.matrix(y).T
        a = multiplier * y
        error = y - basis * a
        error_values.append(np.linalg.norm(np.array(error)))

    df['error_value'] = error_values
    df['error_value'].to_csv('error_values.csv', encoding='utf-8-sig')


if __name__ == '__main__':
    main()
