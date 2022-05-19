import matplotlib.pyplot as plt
import numpy as np
import pandas as pd


def main():
    # 基底の読み込み
    with open('SETTINGS') as f:
        settings_l = f.readlines()
    n = int(settings_l[0].split()[0]) + 1
    params_count = int(settings_l[2])
    basis_count = int(settings_l[-1].split()[1])

    with open('02_Vk') as f:
        basis_l = f.readlines()

    basis = np.matrix(np.array(basis_l, dtype=float).reshape([basis_count, n])).T
    multiplier = (((basis.T * basis) + 0.00001 * np.eye(basis_count)) ** -1) * basis.T

    fig = plt.figure()
    ax = fig.add_subplot(111, title='basis mode', xlabel='node', ylabel='value')
    ax.plot(basis)
    fig.savefig('basis_mode.png')

    df = pd.read_csv('OUTPUTALL.csv')
    ys = df.iloc[:, params_count:].values

    error_values = []
    for y in ys:
        y = np.matrix(y).T
        a = multiplier * y
        error = y - basis * a
        error_values.append(np.linalg.norm(np.array(error)))

    df['error_value'] = error_values
    output_l = [f'param{i+1}' for i in range(params_count)]
    output_l.append('error_value')
    df[output_l].to_csv('error_values.csv', encoding='utf-8-sig')

    if params_count == 1:
        fig_error = plt.figure()
        ax_error = fig_error.add_subplot(111, xlabel='param1', ylabel='error', title='error_value')
        x = df['param1']
        y = df['error_value']
        ax_error.plot(x, y)
        fig_error.savefig('error.png')
    elif params_count == 2:
        fig_error = plt.figure()
        ax_error = fig_error.add_subplot(
            projection='3d', xlabel='param1', ylabel='param2', zlabel='error', title='error_value'
        )
        x = df['param1']
        y = df['param2']
        z = df['error_value']
        ax_error.plot(x, y, z)
        fig_error.savefig('error.png')


if __name__ == '__main__':
    main()
