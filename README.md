# heat_conduction_fem
## 実行方法
1. simulate.cに諸々の条件を記述する
2. `make re`を実行する
3. `./simulate.out`を実行する
4. 出力された`PARAMETERS`と`SNAPSHOT`をPODBASIS_EXTRACTIONにコピペする
5. PODBASIS_EXTRACTIONを実行する
6. 出力された`02_Vk`をこのディレクトリにコピペする
7. `python evaluate_basis.py`を実行する
8. `error_values.csv`に各パラメータにおける誤差の値が出力されます
