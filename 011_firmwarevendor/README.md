# UEFIのファームウェアベンダーを表示するサンプル
`EFI_SYSTEM_TABLE`構造体の`FirmwareVendor`メンバに格納されているファームウェアベンダーを表示するサンプルです。

`make run`等で実行すると、"Hello UEFI!"の次の行に`FirmwareVendor`メンバの内容が表示されます。
(QEMUでOVMFを使用している場合、"EDK II"と表示されます。)
