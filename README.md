# heat_conduction_fem

# SETTINGSの設定方法
```
要素数NE 全体長さL 断面積A 熱伝導率λ
境界条件種別（x=0） 境界条件種別（x=L） 境界条件値（x=0） 境界条件値（x=L）
パラメータ数
パラメータ1最小値 パラメータ1最大値 パラメータ1分割数
...
パラメータn最小値 パラメータn最大値 パラメータn分割数
サンプル率 基底数
```

## 実行方法
1. `SETTINGS`と`simulate.c`に諸々の条件を記述する
2. `make re`を実行する
3. `./simulate.out`を実行する
4. 出力された`PARAMETERS`と`SNAPSHOT`をPODBASIS_EXTRACTIONにコピペする
5. PODBASIS_EXTRACTIONを実行する
6. 出力された`02_Vk`をこのディレクトリにコピペする
7. `python evaluate_basis.py`を実行する
8. `error_values.csv`に各パラメータにおける誤差の値が出力されます
