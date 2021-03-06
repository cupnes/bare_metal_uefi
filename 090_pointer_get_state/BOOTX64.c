#define DEV_PATH_NAME_LEN	16
#define FILE_PATH_NAME_LEN	3

#define NULL		(void *)0
#define TRUE		1
#define FALSE		0
#define EFIERR(a)	(0x8000000000000000 | a)
#define EFI_SUCCESS	0
#define EFI_INVALID_PARAMETER	EFIERR(2)
#define EFI_DEVICE_ERROR	EFIERR(7)

//*******************************************************
// Open Modes
//*******************************************************
#define EFI_FILE_MODE_READ	0x0000000000000001
#define EFI_FILE_MODE_WRITE	0x0000000000000002
#define EFI_FILE_MODE_CREATE	0x8000000000000000
//*******************************************************
// File Attributes
//*******************************************************
#define EFI_FILE_READ_ONLY	0x0000000000000001
#define EFI_FILE_HIDDEN	0x0000000000000002
#define EFI_FILE_SYSTEM	0x0000000000000004
#define EFI_FILE_RESERVED	0x0000000000000008
#define EFI_FILE_DIRECTORY	0x0000000000000010
#define EFI_FILE_ARCHIVE	0x0000000000000020
#define EFI_FILE_VALID_ATTR	0x0000000000000037

#define EVT_TIMER	0x80000000
#define EVT_RUNTIME	0x40000000
#define EVT_NOTIFY_WAIT	0x00000100
#define EVT_NOTIFY_SIGNAL	0x00000200
#define EVT_SIGNAL_EXIT_BOOT_SERVICES	0x00000201
#define EVT_SIGNAL_VIRTUAL_ADDRESS_CHANGE	0x60000202

#define MEDIA_DEVICE_PATH	0x04
#define MEDIA_FILEPATH_DP	0x04

#define END_DEVICE_PATH_TYPE	0x7f
#define END_ENTIRE_DEVICE_PATH_SUBTYPE	0xff

#define EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL	0x00000001
#define EFI_OPEN_PROTOCOL_GET_PROTOCOL		0x00000002
#define EFI_OPEN_PROTOCOL_TEST_PROTOCOL		0x00000004
#define EFI_OPEN_PROTOCOL_BY_CHILD_CONTROLLER	0x00000008
#define EFI_OPEN_PROTOCOL_BY_DRIVER		0x00000010
#define EFI_OPEN_PROTOCOL_EXCLUSIVE		0x00000020

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

struct EFI_DEVICE_PATH_PROTOCOL {
	unsigned char Type;
	unsigned char SubType;
	unsigned char Length[2];
};

enum EFI_TIMER_DELAY {
	TimerCancel,
	TimerPeriodic,
	TimerRelative
};

//*******************************************************
//EFI_MEMORY_TYPE
//*******************************************************
// These type values are discussed in Table 24 and Table 25.
enum EFI_MEMORY_TYPE {
	EfiReservedMemoryType,
	EfiLoaderCode,
	EfiLoaderData,
	EfiBootServicesCode,
	EfiBootServicesData,
	EfiRuntimeServicesCode,
	EfiRuntimeServicesData,
	EfiConventionalMemory,
	EfiUnusableMemory,
	EfiACPIReclaimMemory,
	EfiACPIMemoryNVS,
	EfiMemoryMappedIO,
	EfiMemoryMappedIOPortSpace,
	EfiPalCode,
	EfiMaxMemoryType
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

		//
		// Task Priority Services
		//
		unsigned long long _buf2[2];

		//
		// Memory Services
		//
		unsigned long long _buf3[3];
		unsigned long long (*AllocatePool)(
			enum EFI_MEMORY_TYPE PoolType,
			unsigned long long Size,
			void **Buffer);
		unsigned long long (*FreePool)(
			void **Buffer);

		//
		// Event & Timer Services
		//
		unsigned long long (*CreateEvent)(
			unsigned int Type,
			unsigned long long NotifyTpl,
			void (*NotifyFunction)(void *Event, void *Context),
			void *NotifyContext,
			void *Event);
		unsigned long long (*SetTimer)(void *Event,
					       enum EFI_TIMER_DELAY Type,
					       unsigned long long TriggerTime);
		unsigned long long (*WaitForEvent)(
			unsigned long long NumberOfEvents,
			void *Event,
			unsigned long long *Index);
		unsigned long long _buf4[3];

		//
		// Protocol Handler Services
		//
		unsigned long long _buf5[3];
		unsigned long long (*HandleProtocol)(
			void *Handle,
			struct EFI_GUID *Protocol,
			void **Interface);
		unsigned long long _buf5_2[5];

		//
		// Image Services
		//
		unsigned long long (*LoadImage)(
			unsigned char BootPolicy,
			void *ParentImageHandle,
			struct EFI_DEVICE_PATH_PROTOCOL *DevicePath,
			void *SourceBuffer,
			unsigned long long SourceSize,
			void **ImageHandle);
		unsigned long long (*StartImage)(
			void *ImageHandle,
			unsigned long long *ExitDataSize,
			unsigned short **ExitData);
		unsigned long long _buf6[3];

		//
		// Miscellaneous Services
		//
		unsigned long long _buf7[2];
		unsigned long long (*SetWatchdogTimer)(
			unsigned long long Timeout,
			unsigned long long WatchdogCode,
			unsigned long long DataSize,
			unsigned short *WatchdogData);

		//
		// DriverSupport Services
		//
		unsigned long long _buf8[2];

		//
		// Open and Close Protocol Services
		//
		unsigned long long (*OpenProtocol)(
			void *Handle,
			struct EFI_GUID *Protocol,
			void **Interface,
			void *AgentHandle,
			void *ControllerHandle,
			unsigned int Attributes);
		unsigned long long _buf9[2];

		//
		// Library Services
		//
		unsigned long long _buf10[2];
		unsigned long long (*LocateProtocol)(struct EFI_GUID *, void *, void **);
		unsigned long long _buf11[2];

		//
		// 32-bit CRC Services
		//
		unsigned long long _buf12;

		//
		// Miscellaneous Services
		//
		unsigned long long _buf13[3];
	} *BootServices;
};

struct EFI_SIMPLE_POINTER_STATE {
	int RelativeMovementX;
	int RelativeMovementY;
	int RelativeMovementZ;
	unsigned char LeftButton;
	unsigned char RightButton;
};

struct EFI_SIMPLE_POINTER_MODE {
	unsigned long long ResolutionX;
	unsigned long long ResolutionY;
	unsigned long long ResolutionZ;
	unsigned char LeftButton;
	unsigned char RightButton;
};

struct EFI_SIMPLE_POINTER_PROTOCOL {
	unsigned long long (*Reset)(
		struct EFI_SIMPLE_POINTER_PROTOCOL *This,
		unsigned char ExtendedVerification);
	unsigned long long (*GetState)(
		struct EFI_SIMPLE_POINTER_PROTOCOL *This,
		struct EFI_SIMPLE_POINTER_STATE *State);
	void *WaitForInput;
	struct EFI_SIMPLE_POINTER_MODE *Mode;
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

struct EFI_FILE_PROTOCOL {
	unsigned long long Revision;
	unsigned long long (*Open)(struct EFI_FILE_PROTOCOL *This,
				   struct EFI_FILE_PROTOCOL **NewHandle,
				   unsigned short *FileName,
				   unsigned long long OpenMode,
				   unsigned long long Attributes);
	unsigned long long (*Close)(struct EFI_FILE_PROTOCOL *This);
	unsigned long long (*Delete)(struct EFI_FILE_PROTOCOL *This);
	unsigned long long (*Read)(struct EFI_FILE_PROTOCOL *This,
				   unsigned long long *BufferSize,
				   void *Buffer);
	unsigned long long (*Write)(struct EFI_FILE_PROTOCOL *This,
				    unsigned long long *BufferSize,
				    void *Buffer);
	unsigned long long (*GetPosition)(struct EFI_FILE_PROTOCOL *This,
					  unsigned long long *Position);
	unsigned long long (*SetPosition)(struct EFI_FILE_PROTOCOL *This,
					  unsigned long long Position);
	unsigned long long (*GetInfo)(struct EFI_FILE_PROTOCOL *This,
				      struct EFI_GUID *InformationType,
				      unsigned long long *BufferSize,
				      void *Buffer);
	unsigned long long (*SetInfo)(struct EFI_FILE_PROTOCOL *This,
				      struct EFI_GUID *InformationType,
				      unsigned long long BufferSize,
				      void *Buffer);
	unsigned long long (*Flush)(struct EFI_FILE_PROTOCOL *This);
};

struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL {
	unsigned long long Revision;
	unsigned long long (*OpenVolume)(
		struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *This,
		struct EFI_FILE_PROTOCOL **Root);
};

struct EFI_LOADED_IMAGE_PROTOCOL {
	unsigned int Revision;
	void *ParentHandle;
	struct EFI_SYSTEM_TABLE *SystemTable;
	// Source location of the image
	void *DeviceHandle;
	struct EFI_DEVICE_PATH_PROTOCOL *FilePath;
	void *Reserved;
	// Image’s load options
	unsigned int LoadOptionsSize;
	void *LoadOptions;
	// Location where image was loaded
	void *ImageBase;
	unsigned long long ImageSize;
	enum EFI_MEMORY_TYPE ImageCodeType;
	enum EFI_MEMORY_TYPE ImageDataType;
	unsigned long long (*Unload)(void *ImageHandle);
};

struct EFI_CPU_PHYSICAL_LOCATION {
	unsigned int Package;
	unsigned int Core;
	unsigned int Thread;
};

struct EFI_PROCESSOR_INFORMATION {
	unsigned long long ProcessorId;
	unsigned int StatusFlag;
	struct EFI_CPU_PHYSICAL_LOCATION Location;
};

struct EFI_MP_SERVICES_PROTOCOL {
	unsigned long long (*GetNumberOfProcessors)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		unsigned long long *NumberOfProcessors,
		unsigned long long *NumberOfEnabledProcessors);
	unsigned long long (*GetProcessorInfo)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		unsigned long long ProcessorNumber,
		struct EFI_PROCESSOR_INFORMATION *ProcessorInfoBuffer);
	unsigned long long (*StartupAllAPs)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		void (*Procedure)(void *ProcedureArgument),
		unsigned char SingleThread,
		void *WaitEvent,
		unsigned long long TimeoutInMicroSeconds,
		void *ProcedureArgument,
		unsigned long long **FailedCpuList);
	unsigned long long (*StartupThisAP)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		void (*Procedure)(void *ProcedureArgument),
		unsigned long long ProcessorNumber,
		void *WaitEvent,
		unsigned long long TimeoutInMicroseconds,
		void *ProcedureArgument,
		unsigned char *Finished);
	unsigned long long (*SwitchBSP)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		unsigned long long ProcessorNumber,
		unsigned char EnableOldBSP);
	unsigned long long (*EnableDisableAP)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		unsigned long long ProcessorNumber,
		unsigned char EnableAP,
		unsigned int *HealthFlag);
	unsigned long long (*WhoAmI)(
		struct EFI_MP_SERVICES_PROTOCOL *This,
		unsigned long long *ProcessorNumber);
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
			case '\r':
				str[i] = L'\r';
				break;
			case '\n':
				str[i] = L'\n';
				break;
			}
		}
	}

	str[i] = L'\0';
	return str;
}

volatile unsigned char lock_conout = 0;
void puts(unsigned short *str, struct EFI_SYSTEM_TABLE *SystemTable)
{
	while (lock_conout);
	lock_conout = 1;
	SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
	lock_conout = 0;
}

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned short str[1024];
	unsigned long long status;

	struct EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};
	struct EFI_SIMPLE_POINTER_PROTOCOL *spp;

	puts(L"start of 0A0_pointer\r\n", SystemTable);

	status = SystemTable->BootServices->LocateProtocol(&spp_guid, NULL, (void **)&spp);
	if (status) {
		puts(L"error: SystemTable->BootServices->LocateProtocol\r\n", SystemTable);
		while (1);
	}

	status = spp->Reset(spp, FALSE);
	if (status) {
		puts(L"error: spp->Reset\r\n", SystemTable);
		while (1);
	}

	struct EFI_SIMPLE_POINTER_STATE sps;
	volatile unsigned int i;
	while (1) {
		status = spp->GetState(spp, &sps);
		if (!status) {
			puts(L"sps: ", SystemTable);
			puts(int_to_unicode_hex(sps.RelativeMovementX, 8, str), SystemTable);
			puts(L" ", SystemTable);
			puts(int_to_unicode_hex(sps.RelativeMovementY, 8, str), SystemTable);
			puts(L" ", SystemTable);
			puts(int_to_unicode_hex(sps.RelativeMovementZ, 8, str), SystemTable);
			puts(L" ", SystemTable);
			puts(int_to_unicode_hex(sps.LeftButton, 1, str), SystemTable);
			puts(L" ", SystemTable);
			puts(int_to_unicode_hex(sps.RightButton, 1, str), SystemTable);
			puts(L"\r\n", SystemTable);
		}/*  else { */
		/* 	puts(L"error: spp->GetState: ", SystemTable); */
		/* 	puts(int_to_unicode_hex(status, 16, str), SystemTable); */
		/* 	puts(L"\r\n", SystemTable); */
		/* } */

		for (i = 100000; i; i--);
	}

	puts(L"end of 0A0_pointer\r\n", SystemTable);

	while (1);
}
