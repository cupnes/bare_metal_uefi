#define NULL		(void *)0
#define BLT_WIDTH	50
#define BLT_HEIGHT	50
#define EFIERR(a)	(0x8000000000000000 | a)
#define EFI_SUCCESS	0
#define EFI_INVALID_PARAMETER	EFIERR(2)
#define EFI_DEVICE_ERROR	EFIERR(7)

struct EFI_INPUT_KEY {
	unsigned short ScanCode;
	unsigned short UnicodeChar;
};

struct EFI_GUID {
	unsigned int Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
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
	char _buf3[24];
	struct EFI_BOOT_SERVICES {
		char _buf1[24];
		char _buf2[296];
		unsigned long long (*LocateProtocol)(struct EFI_GUID *, void *, void **);
	} *BootServices;
};

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Reserved;
};

enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION {
	EfiBltVideoFill,
	EfiBltVideoToBltBuffer,
	EfiBltBufferToVideo,
	EfiBltVideoToVideo,
	EfiGraphicsOutputBltOperationMax
};

enum EFI_GRAPHICS_PIXEL_FORMAT {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
	void *_buf;
	unsigned long long (*SetMode)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *, unsigned int);
	unsigned long long (*Blt)(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *,
				  struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *,
				  enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION,
				  unsigned long long SourceX, unsigned long long SourceY,
				  unsigned long long DestinationX, unsigned long long DestinationY,
				  unsigned long long Width, unsigned long long Height,
				  unsigned long long Delta);
	struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
		unsigned int MaxMode;
		unsigned int Mode;
		struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
			unsigned int Version;
			unsigned int HorizontalResolution;
			unsigned int VerticalResolution;
			enum EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
			struct EFI_PIXEL_BITMASK {
				unsigned int RedMask;
				unsigned int GreenMask;
				unsigned int BlueMask;
				unsigned int ReservedMask;
			} PixelInformation;
			unsigned int PixelsPerScanLine;
		} *Info;
		unsigned long long SizeOfInfo;
		unsigned long long FrameBufferBase;
		unsigned long long FrameBufferSize;
	} *Mode;
};

unsigned short *int_to_unicode(long long val, unsigned char num_digits, unsigned short str[])
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

unsigned short *int_to_unicode_hex(unsigned long long val, unsigned char num_digits, unsigned short str[])
{
	short i;
	unsigned short v;

	for (i = num_digits - 1; i >= 0; i--) {
		v = (unsigned short)(val & 0x0f);
		if (v < 0xa)
			str[i] = L'0' + v;
		else
			str[i] = L'A' + (v - 0xa);
		val >>= 4;
	}

	str[num_digits] = L'\0';

	return str;
}

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL blt_buf[BLT_WIDTH * BLT_HEIGHT];

void out(struct EFI_SYSTEM_TABLE *SystemTable, struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
	unsigned short str[32];

	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"MaxMode: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->MaxMode, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Mode: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->Mode, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Version: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->Info->Version, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"HorizontalResolution: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->Info->HorizontalResolution, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"VerticalResolution: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->Info->VerticalResolution, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PixelFormat: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->Info->PixelFormat, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"PixelInformation:\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode_hex(gop->Mode->Info->PixelInformation.RedMask, 8, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode_hex(gop->Mode->Info->PixelInformation.GreenMask, 8, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode_hex(gop->Mode->Info->PixelInformation.BlueMask, 8, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode_hex(gop->Mode->Info->PixelInformation.ReservedMask, 8, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"SizeOfInfo: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode(gop->Mode->SizeOfInfo, 10, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"FrameBufferBase: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode_hex(gop->Mode->FrameBufferBase, 16, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"FrameBufferSize: ");
	SystemTable->ConOut->OutputString(SystemTable->ConOut, int_to_unicode_hex(gop->Mode->FrameBufferSize, 16, str));
	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

	switch (gop->Blt(gop, blt_buf, EfiBltBufferToVideo, 0, 0, 200, 0, BLT_WIDTH, BLT_HEIGHT, 0)) {
	case EFI_SUCCESS:
		SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Blt: EFI_SUCCESS\r\n");
		break;
	case EFI_INVALID_PARAMETER:
		SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Blt: EFI_INVALID_PARAMETER\r\n");
		break;
	case EFI_DEVICE_ERROR:
		SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Blt: EFI_DEVICE_ERROR\r\n");
		break;
	default:
		SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Blt: default\r\n");
		break;
	}
}

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
	struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
	struct EFI_INPUT_KEY efi_input_key;
	int i;

	SystemTable->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&gop);

	for (i = 0; i < BLT_HEIGHT * BLT_WIDTH; i++) {
		blt_buf[i].Blue = 255;
		blt_buf[i].Green = 0;
		blt_buf[i].Red = 0;
		blt_buf[i].Reserved = 0;
	}

	while (1) {
		out(SystemTable, gop);
		while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &efi_input_key));
		gop->SetMode(gop, efi_input_key.UnicodeChar - L'0');
	}

	while (1);
}
