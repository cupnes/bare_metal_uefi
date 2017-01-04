struct EFI_SYSTEM_TABLE {
	char _buf1[24];
	unsigned short *FirmwareVendor;
	char _buf2[28];
	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
		void *_buf;
		unsigned long long (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *, unsigned short *);
	} *ConOut;
};

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello UEFI!\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, SystemTable->FirmwareVendor);
	while (1);
}
