struct EFI_INPUT_KEY {
	unsigned short ScanCode;
	unsigned short UnicodeChar;
};

struct EFI_SYSTEM_TABLE {
	char _buf1[44];
	struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
		void *_buf;
		unsigned long long (*ReadKeyStroke)(struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL *, struct EFI_INPUT_KEY *);
	} *ConIn;
	void *_buf2;
	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
		void *_buf;
		unsigned long long (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *, unsigned short *);
	} *ConOut;
};

int DllMainCRTStartup(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_INPUT_KEY efi_input_key;
	unsigned short str[3];

	while (1) {
		if (!SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &efi_input_key)) {
			if (efi_input_key.UnicodeChar != L'\r') {
				str[0] = efi_input_key.UnicodeChar;
				str[1] = L'\0';
			} else {
				str[0] = L'\r';
				str[1] = L'\n';
				str[2] = L'\0';
			}
			SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
		}
	}

	return 0;
}
