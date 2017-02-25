#include "img.h"

#define NULL		(void *)0
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

unsigned short *int_to_ascii_hex(unsigned long long val, unsigned char num_digits, unsigned short str[])
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

void blt(struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop, unsigned char img[], unsigned int img_width, unsigned int img_height)
{
	unsigned char *fb;
	unsigned int i, j, k, vr, hr, ofs = 0;

	fb = (unsigned char *)gop->Mode->FrameBufferBase;
	vr = gop->Mode->Info->VerticalResolution;
	hr = gop->Mode->Info->HorizontalResolution;

	for (i = 0; i < vr; i++) {
		if (i >= img_height)
			break;
		for (j = 0; j < hr; j++) {
			if (j >= img_width) {
				fb += (hr - img_width) * 4;
				break;
			}
			for (k = 0; k < 4; k++)
				*fb++ = img[ofs++];
		}
	}
}

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
	struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop;
	struct EFI_INPUT_KEY efi_input_key;
	unsigned int i;

	SystemTable->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&gop);

	while (1) {
		blt(gop, img[i].addr, img[i].width, img[i].height);
		while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &efi_input_key));
		switch (efi_input_key.UnicodeChar) {
		case L'j':
			if (i < NUM_IMGS - 1)
				i++;
			break;
		case L'k':
			if (i > 0)
				i--;
			break;
		}
	}
}
