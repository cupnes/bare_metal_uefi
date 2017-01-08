# UEFIバージョンを表示するサンプル
実行環境のUEFIのバージョンを表示するサンプルです。

UEFIバージョンは、`EFI_SYSTEM_TABLE`構造体の`BootServices`メンバ(`EFI_BOOT_SERVICES`構造体)内の`Hdr`メンバ(`EFI_TABLE_HEADER`構造体)の`Revision`メンバ(`unsigned int`)に格納されており、
上位2バイトにメジャーバージョン、下位2バイトにマイナーバージョンが格納されています。

例えば、`make run`等でQEMU(OVMF)で実行すると以下のように表示され、
```
UEFI version
- Top Half   : 00002
- Bottom Half: 00040
```
UEFIのバージョンが"2.40"であるとわかります。
