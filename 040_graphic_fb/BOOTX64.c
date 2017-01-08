struct EFI_GUID {
	unsigned int Data1;
	unsigned short Data2;
	unsigned short Data3;
	unsigned char Data4[8];
};

struct EFI_SYSTEM_TABLE {
	char _buf1[60];
	struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
		void *_buf;
		unsigned long long (*OutputString)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *, unsigned short *);
	} *ConOut;
	char _buf2[24];
	struct EFI_BOOT_SERVICES {
		char _buf1[24];
		char _buf2[296];
		unsigned long long (*LocateProtocol)(struct EFI_GUID *, void *, void **);
	} *BootServices;
};

enum EFI_GRAPHICS_PIXEL_FORMAT {
	PixelRedGreenBlueReserved8BitPerColor,
	PixelBlueGreenRedReserved8BitPerColor,
	PixelBitMask,
	PixelBltOnly,
	PixelFormatMax
};

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
	unsigned char Blue;
	unsigned char Green;
	unsigned char Red;
	unsigned char Reserved;
};

struct EFI_GRAPHICS_OUTPUT_PROTOCOL {
	char _buf[24];
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

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
	struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *fb_ptr;
	unsigned int y, x;

	SystemTable->BootServices->LocateProtocol(&gop_guid, 0, (void **)&gop);
	fb_ptr = (struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)gop->Mode->FrameBufferBase;
	for (y = 0; y < gop->Mode->Info->VerticalResolution; y++) {
		for (x = 0; x < gop->Mode->Info->HorizontalResolution; x++) {
			fb_ptr->Blue = 255;
			fb_ptr->Green = 0;
			fb_ptr->Red = 0;
			fb_ptr++;
		}
	}

	while (1);
}
