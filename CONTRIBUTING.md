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

## 命名規則

norminette で検出されるもの（違反すると commit が止まる）

| 対象 | 規則 | 例 |
| --- | --- | --- |
| 変数・関数 | snake_case、小文字・数字・`_` のみ | `map_width`, `load_texture` |
| struct | `s_` + typedef は `t_` | `struct s_player` / `t_player` |
| enum | `e_` + typedef は `t_` | `enum e_dir` / `t_dir` |
| union | `u_` | `union u_color` |
| ファイル名 | snake_case | `parse_map.c` |

グローバル変数は使わない。

プロジェクト独自の規則

| 対象 | 規則 | 例 |
| --- | --- | --- |
| 関数の接頭辞 | モジュール名から始める | `parse_*`, `render_*`, `raycast_*`, `input_*` |
| マクロ・定数 | 大文字の SNAKE_CASE | `WIN_WIDTH`, `TILE_SIZE` |
| 真偽を返す関数 | `is_` / `has_` から始める | `is_wall`, `has_player` |
| 成否を返す関数 | `bool` を返す（成功で `true`） | `bool parse_map(...)` |
| 解放関数 | `free_` / `destroy_` から始める | `free_map`, `destroy_game` |
