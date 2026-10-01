# 開発ガイド

## セットアップ

commit 時に norminette を自動で走らせるため、[lefthook](https://github.com/evilmartians/lefthook) を入れる。

```sh
brew install lefthook   # 未インストールなら
pip install norminette  # 未インストールなら
lefthook install
```

CI（GitHub Actions）でも push / PR ごとに norminette が走る。
