# 開発ガイド

## セットアップ

commit 時に norminette、push 時に `make` を自動で走らせるため、[lefthook](https://github.com/evilmartians/lefthook) を入れる。

```sh
brew install lefthook   # 未インストールなら
pip install norminette  # 未インストールなら
lefthook install
```

CI（GitHub Actions）でも push / PR ごとに norminette とビルドが走る。

## ビルド

```sh
make
```

minilibx-linux が無ければ `make` 時に自動で clone される。Mac は [XQuartz](https://www.xquartz.org/) が必要。
