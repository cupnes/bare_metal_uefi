# スライドショー
imgディレクトリ内の画像をスライドショーするサンプルです。

## 使い方

1. imgディレクトリを作成し、画像を配置
1. img.hの定数 `NUM_IMGS` (画像枚数)とimg.cの `struct IMG img[NUM_IMGS]` の内容を修正
   * `struct IMG` の定義はimg.hを参照
   * `struct IMG` の `addr` メンバは、画像ファイルを `objcopy` でオブジェクトファイル化した際のシンボルへのアドレス
     * `_binary_img_yux_bgra_start` の様な変数名の `yux` の箇所を画像ファイル名へ置き換えれば大丈夫なはず
     * 詳しくはprepare.shとMakefile参照
1. `./prepare.sh && make run`

## 操作

* 'j'キー: 戻る
* 'k'キー: 進む

※ ファイル名順です。
