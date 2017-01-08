# Bare Metal Samples (UEFI application)
ベアメタルプログラミングでUEFIアプリケーションを作成してみたサンプル集です。

「ベアメタルプログラミング」ということで、EDKやgnu-efiといった開発環境やツールチェイン無しで作成しています。

各サンプルの内容については、各サンプルのディレクトリ内のREADME.mdで説明しています。

## 使い方
### 1. 準備
#### 1.1. 必要なパッケージのインストール
`make`、`x86_64-w64-mingw32-gcc`、`qemu-system-x86_64`といったコマンドを使用します。

UbuntuやDebian等のAPTが使用できる環境であれば、以下のパッケージをインストールしてください。

- make
- gcc-mingw-w64-x86-64
- qemu-system-x86_64

#### 1.2. このリポジトリのclone
`git clone https://github.com/cupnes/bare_metal_uefi.git`

#### 1.3. QEMU用のUEFIイメージファイルをリポジトリ直下へ配置
QEMUでUEFIの動作確認を行うためには、UEFIのイメージファイル(`OVMF.fd`)が必要です。

このリポジトリ内の各サンプルのMakefileはリポジトリ直下の`OVMF.fd`を参照するので、`OVMF.fd`をリポジトリ直下へ配置してください。

以下のURLからダウンロード可能です。

- [https://sourceforge.net/projects/edk2/files/OVMF/](https://sourceforge.net/projects/edk2/files/OVMF/)

ダウンロード後、zipを展開し、このリポジトリ直下へ配置してください。
```
$ wget http://downloads.sourceforge.net/project/edk2/OVMF/OVMF-X64-r15214.zip
$ unzip OVMF-X64-r15214.zip
$ mv OVMF.fd bare_metal_uefi/
$ rm BUILD_INFO LICENSE README OVMF-X64-r15214.zip
```

### 2. ビルド・動作確認
各サンプルのディレクトリへ移動し、
`make run`でビルドからQEMU上での動作確認までを行えます。

終了方法は以下のとおりです。

- QEMUを端末内で実行している(Makefileでqemu実行時に-nographicオプションを付けている)
-- `Ctrl + a`の後、`x`
- QEMUを別ウィンドウで実行している
-- ウィンドウを閉じる
-- あるいは、`Ctrl + Alt + 2`でQEMUモニターに入り、`quit`コマンドを実行

なお、実機で動作させる場合は、
USBフラッシュメモリ等の第1パーティションをFATでフォーマットし、
ビルド時に生成されるfsディレクトリの中身をコピーしてください。

■ コマンド例
```
# mount /dev/sdb1 /mnt/storage
# cp -r fs/* /mnt/storage/
# umount /mnt/storage
```

起動ディスク設定を変更し、ここで作成したUSBフラッシュメモリ等でブートすると、
UEFIアプリを試すことができます。
終了する際は、電源ボタンでPCごと終了させて下さい。

## 参考情報
以下の情報を参考にさせてもらい、作成しました。

- [Specifications | Unified Extensible Firmware Interface Forum](http://www.uefi.org/specifications)
- [ツールキットを使わずに UEFI アプリケーションの Hello World! を作る - 品川高廣（東京大学）のブログ](http://d.hatena.ne.jp/shina_ecc/20140819/1408434995)
- [UEFI Bare Bones - OSDev Wiki](http://wiki.osdev.org/UEFI_Bare_Bones)
