# SetMode()とBlt()を使用するサンプル
SetMode()は、ビデオモードを指定したモードへ変更する関数です。
またBlt()は、予め用意したピクセル情報に従って、指定された座標へ画面描画を行ってくれる関数です。

`make run`等でこのサンプルを実行すると、
`Graphics Output Protocol`関係の情報を画面に出力し、50x50の青色単色の矩形を(200,0)の座標へ描画します。
なお、UEFIにおいて、原点(0,0)は画面左上です。

そして、'0'〜'9'キーを押下すると、その番号のビデオモードへ切り替えます。
設定可能なビデオモードは、'0'〜'MaxMode - 1'です。
なお、キー入力のチェックを行っておらず、入力された値をそのまま`SetMode()`へ渡していますので、
`MaxMode`の値は、画面に出力されている値を確認して下さい。

## 備考
Lenovo ThinkPad E450の環境(UEFI v2.3.1)において、ビデオモードを設定可能な0〜3のどれに切り替えても、
Blt()による画面描画ができていません。
(Blt()の戻り値は成功を示しているが、画面に矩形が描画されていない状態。)