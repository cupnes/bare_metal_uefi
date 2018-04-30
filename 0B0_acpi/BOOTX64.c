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
	unsigned long long NumberOfTableEntries;
	struct EFI_CONFIGURATION_TABLE {
		struct EFI_GUID VendorGuid;
		void *VendorTable;
	} *ConfigurationTable;
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

struct EFI_ACPI_TABLE_PROTOCOL {
	unsigned long long (*InstallAcpiTable)(struct EFI_ACPI_TABLE_PROTOCOL *This,
					       void *AcpiTableBuffer,
					       unsigned long long AcpiTableBufferSize,
					       unsigned long long *TableKey);
	unsigned long long (*UninstallAcpiTable)(struct EFI_ACPI_TABLE_PROTOCOL *This,
						 unsigned long long TableKey);
};

struct EFI_GUID EFI_ACPI_20_TABLE_GUID = {
	0x8868e871, 0xe4f1, 0x11d3,
	{0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
struct EFI_GUID ACPI_TABLE_GUID = {
	0xeb9d2d30, 0x2d88, 0x11d3,
	{0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
struct EFI_GUID SAL_SYSTEM_TABLE_GUID = {
	0xeb9d2d32, 0x2d88, 0x11d3,
	{0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
struct EFI_GUID SMBIOS_TABLE_GUID = {
	0xeb9d2d31, 0x2d88, 0x11d3,
	{0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
struct EFI_GUID MPS_TABLE_GUID = {
	0xeb9d2d2f, 0x2d88, 0x11d3,
	{0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
//
// ACPI 2.0 or newer tables should use EFI_ACPI_TABLE_GUID
//
struct EFI_GUID EFI_ACPI_TABLE_GUID = {
	0x8868e871, 0xe4f1, 0x11d3,
	{0xbc, 0x22, 0x0, 0x80, 0xc7, 0x3c, 0x88, 0x81}};
struct EFI_GUID ACPI_10_TABLE_GUID = {
	0xeb9d2d30, 0x2d88, 0x11d3,
	{0x9a, 0x16, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
enum EFI_GUID_DEF_IDX {
	EFI_GUID_DEF_IDX_EFI_ACPI_20_TABLE_GUID,
	EFI_GUID_DEF_IDX_ACPI_TABLE_GUID,
	EFI_GUID_DEF_IDX_SAL_SYSTEM_TABLE_GUID,
	EFI_GUID_DEF_IDX_SMBIOS_TABLE_GUID,
	EFI_GUID_DEF_IDX_MPS_TABLE_GUID,
	EFI_GUID_DEF_IDX_EFI_ACPI_TABLE_GUID,
	EFI_GUID_DEF_IDX_ACPI_10_TABLE_GUID
};
struct {
	struct EFI_GUID *guid;
	unsigned short name[32];
} EFI_GUID_DEF_TABLE[7] = {
	{&EFI_ACPI_20_TABLE_GUID, L"EFI_ACPI_20_TABLE_GUID"},
	{&ACPI_TABLE_GUID, L"ACPI_TABLE_GUID"},
	{&SAL_SYSTEM_TABLE_GUID, L"SAL_SYSTEM_TABLE_GUID"},
	{&SMBIOS_TABLE_GUID, L"SMBIOS_TABLE_GUID"},
	{&MPS_TABLE_GUID, L"MPS_TABLE_GUID"},
	{&EFI_ACPI_TABLE_GUID, L"EFI_ACPI_TABLE_GUID"},
	{&ACPI_10_TABLE_GUID, L"ACPI_10_TABLE_GUID"}};

struct SDTH {
	char Signature[4];
	unsigned int Length;
	unsigned char Revision;
	unsigned char Checksum;
	char OEMID[6];
	char OEM_Table_ID[8];
	unsigned int OEM_Revision;
	unsigned int Creator_ID;
	unsigned int Creator_Revision;
};

struct XSDT {
	struct SDTH Header;
	/* unsigned long long Entry[(Header.Length - sizeof(Header)) / 8]; */
	unsigned long long Entry[10];
};

struct RSDP {
	char Signature[8];
	unsigned char Checksum;
	char OEMID[6];
	unsigned char Revision;
	unsigned int RsdtAddress;
	unsigned int Length;
	struct XSDT *XsdtAddress;
	unsigned char Extended_Checksum;
	unsigned char Reserved[3];
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

unsigned short *ascii_to_unicode(char ascii[], unsigned char num_digits, unsigned short str[])
{
	unsigned char i;

	for (i = 0; i < num_digits; i++) {
		if (ascii[i] == '\0') {
			str[i] = L'\0';
			break;
		}

		if ('0' <= ascii[i] && ascii[i] <= '9')
			str[i] = L'0' + (ascii[i] - '0');
		else if ('A' <= ascii[i] && ascii[i] <= 'Z')
			str[i] = L'A' + (ascii[i] - 'A');
		else if ('a' <= ascii[i] && ascii[i] <= 'z')
			str[i] = L'a' + (ascii[i] - 'a');
		else {
			switch (ascii[i]) {
			case ' ':
				str[i] = L' ';
				break;
			case '-':
				str[i] = L'-';
				break;
			case '+':
				str[i] = L'+';
				break;
			case '*':
				str[i] = L'*';
				break;
			case '/':
				str[i] = L'/';
				break;
			case '&':
				str[i] = L'&';
				break;
			case '|':
				str[i] = L'|';
				break;
			case '%':
				str[i] = L'%';
				break;
			case '#':
				str[i] = L'#';
				break;
			case '!':
				str[i] = L'!';
				break;
			}
		}
	}

	return str;
}

long long guidcmp(struct EFI_GUID *a, struct EFI_GUID *b)
{
	long long res;
	unsigned char i;

	res = a->Data1 - b->Data1;
	if (res)
		return res;
	res = a->Data2 - b->Data2;
	if (res)
		return res;
	res = a->Data3 - b->Data3;
	if (res)
		return res;
	for (i = 0; i < 8; i++) {
		res = a->Data4[i] - b->Data4[i];
		if (res)
			return res;
	}
	return 0;
}

void puts(unsigned short *str, struct EFI_SYSTEM_TABLE *SystemTable)
{
	SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
}

void PeiCopyMem(void *Destination, void *Source, unsigned long long Length)
{
	char *Destination8;
	char *Source8;

	Destination8  = Destination;
	Source8       = Source;
	while (Length--) {
		*(Destination8++) = *(Source8++);
	}
}

void CopyMem(void *Destination, void *Source, unsigned long long Length)
{
	PeiCopyMem(Destination, Source, Length);
}

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long i;
	unsigned char j;
	unsigned short str[1024];
	struct RSDP *rsdp;
	unsigned int number_of_xsdt_entries;
	char *ascii_p;
	volatile char chr;
	unsigned char *byte_p;

	for (i = 0; i < SystemTable->NumberOfTableEntries; i++) {
		puts(int_to_unicode(i, 1, str), SystemTable);
		puts(L":", SystemTable);
		puts(ascii_to_unicode((char *)SystemTable->ConfigurationTable[i].VendorTable, 8, str), SystemTable);
		puts(L":", SystemTable);
		puts(int_to_unicode_hex(SystemTable->ConfigurationTable[i].VendorGuid.Data1, 8, str), SystemTable);
		puts(L" ", SystemTable);
		puts(int_to_unicode_hex(SystemTable->ConfigurationTable[i].VendorGuid.Data2, 4, str), SystemTable);
		puts(L" ", SystemTable);
		puts(int_to_unicode_hex(SystemTable->ConfigurationTable[i].VendorGuid.Data3, 4, str), SystemTable);
		puts(L" ", SystemTable);
		for (j = 0; j < 8; j++) {
			puts(int_to_unicode_hex(SystemTable->ConfigurationTable[i].VendorGuid.Data4[j], 2, str), SystemTable);
			puts(L" ", SystemTable);
		}
		for (j = 0; j < 7; j++) {
			if (!guidcmp(&SystemTable->ConfigurationTable[i].VendorGuid, EFI_GUID_DEF_TABLE[j].guid)) {
				puts(EFI_GUID_DEF_TABLE[j].name, SystemTable);
				puts(L" ", SystemTable);
				if (j == EFI_GUID_DEF_IDX_EFI_ACPI_20_TABLE_GUID) {
					rsdp = SystemTable->ConfigurationTable[i].VendorTable;
					puts(L"RSDP ", SystemTable);
				}
			}
		}
		puts(L"\r\n", SystemTable);
	}

	puts(ascii_to_unicode((char *)rsdp->XsdtAddress, 4, str), SystemTable);
	puts(L"\r\n", SystemTable);

	puts(L"sizeof SDTH: ", SystemTable);
	puts(int_to_unicode(sizeof(struct SDTH), 3, str), SystemTable);
	puts(L"\r\n", SystemTable);
	puts(L"XSDT Length: ", SystemTable);
	puts(int_to_unicode(rsdp->XsdtAddress->Header.Length, 3, str), SystemTable);
	puts(L"\r\n", SystemTable);
	/* puts(L"Entry_0: ", SystemTable); */
	/* ascii_p = (char *)rsdp->XsdtAddress->Entry_0->Signature; */
	/* puts(ascii_to_unicode(ascii_p, 4, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* puts(int_to_unicode_hex(rsdp->XsdtAddress->Entry_0, 16, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* ascii_p = (char *)rsdp->XsdtAddress->Entry_0; */
	/* puts(L"ascii_p: ", SystemTable); */
	/* puts(ascii_to_unicode(ascii_p, 4, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* chr = *ascii_p; */
	/* puts(L"hoge", SystemTable); */

	/* struct XSDT *Xsdt; */
	/* unsigned long long BasePtr; */
	/* unsigned long long EntryPtr; */
	/* struct SDTH *Table; */
	/* Xsdt = rsdp->XsdtAddress; */
	/* BasePtr = (unsigned long long)(&(Xsdt->Entry)); */
	/* puts(L"BasePtr: ", SystemTable); */
	/* puts(int_to_unicode_hex(BasePtr, 16, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* CopyMem(&EntryPtr, (void *)BasePtr, sizeof(unsigned long long)); */
	/* puts(L"EntryPtr: ", SystemTable); */
	/* puts(int_to_unicode_hex(EntryPtr, 16, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* Table = (struct SDTH *)((unsigned long long)EntryPtr); */
	/* puts(L"Table->Signature: ", SystemTable); */
	/* puts(ascii_to_unicode(Table->Signature, 4, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */

	struct XSDT *xsdt = rsdp->XsdtAddress;
	unsigned int entries = (xsdt->Header.Length - sizeof(xsdt->Header)) / 8;
	/* struct SDTH *h = (struct SDTH *)xsdt->Entry[0]; */
	/* puts(L"XSDT[0]: ", SystemTable); */
	/* puts(ascii_to_unicode(h->Signature, 4, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* puts(L"entries: ", SystemTable); */
	/* puts(int_to_unicode(entries, 2, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* for (i = 0; i < entries; i++) { */
	/* 	puts(L"xsdt->Entry[", SystemTable); */
	/* 	puts(int_to_unicode(i, 1, str), SystemTable); */
	/* 	puts(L"]: ", SystemTable); */
	/* 	puts(int_to_unicode_hex(xsdt->Entry[i], 16, str), SystemTable); */
	/* 	puts(L"\r\n", SystemTable); */
	/* } */
	/*
	 xsdt->Entry[0]: 07F2A00000000000
	 xsdt->Entry[1]: 07F2800000000000
	 xsdt->Entry[2]: 0000000000000000
	*/

	/* for (i = 0; i < entries; i++) { */
	/* 	byte_p = (unsigned char *)&xsdt->Entry[i]; */
	/* 	puts(L"xsdt->Entry[", SystemTable); */
	/* 	puts(int_to_unicode(i, 1, str), SystemTable); */
	/* 	puts(L"]: ", SystemTable); */
	/* 	for (j = 0; j < 8; j++) { */
	/* 		puts(int_to_unicode_hex(*byte_p++, 2, str), SystemTable); */
	/* 		puts(L" ", SystemTable); */
	/* 	} */
	/* 	puts(L"\r\n", SystemTable); */
	/* } */
	/*
	  xsdt->Entry[0]: 00 00 00 00 00 A0 F2 07
	  xsdt->Entry[1]: 00 00 00 00 00 80 F2 07
	  xsdt->Entry[2]: 00 00 00 00 00 00 00 00
	 */

	/* puts(L"0x07F2A00000000000: ", SystemTable); */
	/* byte_p = (unsigned char *)0x07F2A00000000000; */
	/* puts(int_to_unicode_hex((unsigned long long)byte_p, 16, str), SystemTable); */
	/* puts(L"\r\n", SystemTable); */
	/* /\* 0x07F2A00000000000: 07F2A00000000000 *\/ */

	/* volatile unsigned char byte; */
	/* puts(L"0x07F2800000000000: ", SystemTable); */
	/* /\* byte_p = (unsigned char *)0x07F2800000000000; *\/ */
	/* /\* puts(int_to_unicode_hex(*byte_p, 16, str), SystemTable); *\/ */
	/* byte = *byte_p;		/\* => NG *\/ */
	/* puts(L"OK\r\n", SystemTable); */

	struct EFI_GUID atp_guid = {0xffe06bdd, 0x6107, 0x46a6, {0x7b, 0xb2, 0x5a, 0x9c, 0x7e, 0xc5, 0x27, 0x5c}};
	struct EFI_ACPI_TABLE_PROTOCOL *atp;

	unsigned long long status = SystemTable->BootServices->LocateProtocol(&atp_guid, NULL, (void **)&atp);
	if (status) {
		puts(L"error: SystemTable->BootServices->LocateProtocol\r\n", SystemTable);
		while (1);
	}

	struct XSDT my_xsdt;
	CopyMem((void *)&my_xsdt, (void *)xsdt, sizeof(struct XSDT));

	puts(L"== before ==\r\n", SystemTable);
	for (i = 0; i < 10; i++) {
		puts(L"my_xsdt.Entry[", SystemTable);
		puts(int_to_unicode(i, 2, str), SystemTable);
		puts(L"]: 0x", SystemTable);
		puts(int_to_unicode_hex(my_xsdt.Entry[i], 16, str), SystemTable);
		puts(L"\r\n", SystemTable);
	}
	/*
	  == before ==
	  my_xsdt.Entry[00]: 0x07F2A00000000000
	  my_xsdt.Entry[01]: 0x07F2800000000000
	  my_xsdt.Entry[02]: 0x0000000000000000
	  my_xsdt.Entry[03]: 0x0000000000000000
	  my_xsdt.Entry[04]: 0x0000000000000000
	  my_xsdt.Entry[05]: 0x0000000000000000
	  my_xsdt.Entry[06]: 0x0000000000000000
	  my_xsdt.Entry[07]: 0x0000000000000000
	  my_xsdt.Entry[08]: 0x0000000000000000
	  my_xsdt.Entry[09]: 0x0000000000000000
	 */

	unsigned long long TableKey;
	status = atp->InstallAcpiTable(atp, (void *)&my_xsdt, my_xsdt.Header.Length, &TableKey);
	if (status) {
		puts(L"error: atp->InstallAcpiTable\r\n", SystemTable);
		while (1);
	}

	puts(L"== after ==\r\n", SystemTable);
	for (i = 0; i < 10; i++) {
		puts(L"my_xsdt.Entry[", SystemTable);
		puts(int_to_unicode(i, 2, str), SystemTable);
		puts(L"]: 0x", SystemTable);
		puts(int_to_unicode_hex(my_xsdt.Entry[i], 16, str), SystemTable);
		puts(L"\r\n", SystemTable);
	}
	/*
	  == after ==
	  my_xsdt.Entry[00]: 0x07F2A00000000000
	  my_xsdt.Entry[01]: 0x07F2800000000000
	  my_xsdt.Entry[02]: 0x0000000000000000
	  my_xsdt.Entry[03]: 0x0000000000000000
	  my_xsdt.Entry[04]: 0x0000000000000000
	  my_xsdt.Entry[05]: 0x0000000000000000
	  my_xsdt.Entry[06]: 0x0000000000000000
	  my_xsdt.Entry[07]: 0x0000000000000000
	  my_xsdt.Entry[08]: 0x0000000000000000
	  my_xsdt.Entry[09]: 0x0000000000000000
	 */

	struct SDTH *h = (struct SDTH *)my_xsdt.Entry[0];
	puts(L"XSDT[0]: ", SystemTable);
	puts(ascii_to_unicode(h->Signature, 4, str), SystemTable);
	puts(L"\r\n", SystemTable);

	while (1);
}
