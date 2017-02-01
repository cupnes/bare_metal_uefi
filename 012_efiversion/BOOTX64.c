struct EFI_SYSTEM_TABLE {
	struct {
		unsigned long long Signature;
		unsigned int Revision;
		unsigned int HeaderSize;
		unsigned int CRC32;
		unsigned int Reserved;
	} Hdr;
	char _buf1[36];
	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
		void *_buf;
		unsigned long long (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *, unsigned short *);
	} *ConOut;
	char _buf2[24];
	struct {
		struct {
			unsigned long long Signature;
			unsigned int Revision;
			unsigned int HeaderSize;
			unsigned int CRC32;
			unsigned int Reserved;
		} Hdr;
	} *BootServices;
};

unsigned short *int_to_ascii(long long val, unsigned char num_digits, unsigned short str[])
{
	unsigned char digits_base = 0;
	char i;

	if (val < 0) {
		str[digits_base++] = L'-';
		val *= -1;
	}

	for (i = num_digits - 1; i >= 0; i--) {
		str[digits_base + i] = L'0' + (val % 10);
		val /= 10;
	}

	str[digits_base + num_digits] = L'\0';

	return str;
}

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned short str[4];

	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"UEFI version\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"- Top Half   : ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_ascii(
						  SystemTable->Hdr.Revision >> 16,
						  5, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"- Bottom Half: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_ascii(
						  SystemTable->Hdr.Revision & 0x0000ffff,
						  5, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

	while (1);
}
