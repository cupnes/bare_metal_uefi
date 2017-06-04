#define DEV_PATH_NAME_LEN	16
#define FILE_PATH_NAME_LEN	3

#ifndef QEMU
#define FILE_RECT_START_X	10
#define FILE_RECT_START_Y	20
#else
#define FILE_RECT_START_X	90
#define FILE_RECT_START_Y	80
#endif /* QEMU */
#define RECT_WIDTH_PER_CH	12
#define FILE_RECT_HEIGHT	20
#define FILE_MARGIN_WIDTH	7

#define WAIT_MOUSE_POLL		100000

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
		char _buf2[32];
		unsigned long long (*ClearScreen)(struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *);
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

//*******************************************************
//EFI_TIME
//*******************************************************
// This represents the current time information
struct EFI_TIME {
	unsigned short Year; // 1900 – 9999
	unsigned char Month; // 1 – 12
	unsigned char Day; // 1 – 31
	unsigned char Hour; // 0 – 23
	unsigned char Minute; // 0 – 59
	unsigned char Second; // 0 – 59
	unsigned char Pad1;
	unsigned int Nanosecond; // 0 – 999,999,999
	unsigned short TimeZone; // -1440 to 1440 or 2047
	unsigned char Daylight;
	unsigned char Pad2;
};

struct EFI_FILE_INFO {
	unsigned long long Size;
	unsigned long long FileSize;
	unsigned long long PhysicalSize;
	struct EFI_TIME CreateTime;
	struct EFI_TIME LastAccessTime;
	struct EFI_TIME ModificationTime;
	unsigned long long Attribute;
	unsigned short FileName[];
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

struct LIST {
	struct LIST *next;
	struct LIST *prev;
};

struct RECT {
	unsigned int x;
	unsigned int y;
	unsigned int width;
	unsigned int height;
};

struct FILE_LIST {
	struct LIST list;
	struct RECT rect;
	unsigned int size;
	unsigned short name[];
};

void *IH;
struct EFI_SYSTEM_TABLE *ST;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;
struct EFI_SIMPLE_POINTER_PROTOCOL *SPP;
struct LIST FILE_LIST_HEAD;
unsigned short BUF_STR[1024];

unsigned long long strlen(const unsigned short str[])
{
	unsigned long long i = 0;
	while (str[i++]);
	return i;
}

void memcpy(unsigned char *dst, unsigned char *src, unsigned long long size)
{
	while (size--)
		*dst++ = *src++;
}

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

void check_status(unsigned long long status, unsigned short *name, struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned short str[34];

	if (status) {
		puts(L"error: ", SystemTable);
		puts(name, SystemTable);
		puts(L": ", SystemTable);
		puts(int_to_unicode_hex(status, 16, str), SystemTable);
		puts(L"\r\n", SystemTable);
		while (1);
	}
}

void queue_init(struct LIST *head)
{
	head->next = head;
	head->prev = head;
}

void queue_enq(struct LIST *entry, struct LIST *head)
{
	entry->prev = head->prev;
	entry->next = head;
	head->prev->next = entry;
	head->prev = entry;
}

void draw_pixel(unsigned int x, unsigned int y,
		struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color,
		struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
	unsigned int hr = gop->Mode->Info->HorizontalResolution;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base =
		(struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)gop->Mode->FrameBufferBase;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x;

	p->Blue = color.Blue;
	p->Green = color.Green;
	p->Red = color.Red;
	p->Reserved = color.Reserved;
}

struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL get_pixel(unsigned int x, unsigned int y)
{
	unsigned int hr = GOP->Mode->Info->HorizontalResolution;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *base =
		(struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)GOP->Mode->FrameBufferBase;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL *p = base + (hr * y) + x;

	return *p;
}

void draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h,
	       struct EFI_GRAPHICS_OUTPUT_PROTOCOL *gop)
{
	unsigned int i;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL color = {0xff, 0xff, 0xff, 0xff};

	for (i = x; i < (x + w); i++)
		draw_pixel(i, y, color, gop);
	for (i = x; i < (x + w); i++)
		draw_pixel(i, y + h - 1, color, gop);

	for (i = y; i < (y + h); i++)
		draw_pixel(x, i, color, gop);
	for (i = y; i < (y + h); i++)
		draw_pixel(x + w - 1, i, color, gop);
}

void init_protocols(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long status;
	struct EFI_GUID gop_guid = {0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}};
	struct EFI_GUID sfsp_guid = {0x0964e5b22, 0x6459,0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}};
	struct EFI_GUID spp_guid = {0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}};

	IH = ImageHandle;
	ST = SystemTable;

	status = SystemTable->BootServices->LocateProtocol(&gop_guid, NULL, (void **)&GOP);
	check_status(status, L"LocateProtocol(GOP)", ST);

	status = SystemTable->BootServices->LocateProtocol(&sfsp_guid, NULL, (void **)&SFSP);
	check_status(status, L"LocateProtocol(SFSP)", ST);

	status = SystemTable->BootServices->LocateProtocol(&spp_guid, NULL, (void **)&SPP);
	check_status(status, L"LocateProtocol(SPP)", ST);
}

#define MAX_FILE_BUF	1024
void draw_file_list(void)
{
	unsigned long long status;

	struct EFI_FILE_PROTOCOL *root;
	unsigned long long buf_size = MAX_FILE_BUF;
	char file_buf[MAX_FILE_BUF];

	status = SFSP->OpenVolume(SFSP, &root);
	check_status(status, L"OpenVolume", ST);

	struct EFI_FILE_INFO *efi;
	unsigned long long file_name_size;
	unsigned long long file_entry_size;
	struct FILE_LIST *file_entry;

	while (buf_size) {
		buf_size = MAX_FILE_BUF;
		status = root->Read(root, &buf_size, (void *)file_buf);
		check_status(status, L"Read", ST);
		if (buf_size) {
			efi = (struct EFI_FILE_INFO *)file_buf;
			file_name_size = efi->Size - sizeof(struct EFI_FILE_INFO);
			file_entry_size = sizeof(struct FILE_LIST) + file_name_size;
			status = ST->BootServices->AllocatePool(
				EfiBootServicesData, file_entry_size,
				(void **)&file_entry);
			check_status(status, L"AllocatePool", ST);
			file_entry->size = file_entry_size;
			memcpy((unsigned char *)file_entry->name,
			       (unsigned char *)efi->FileName, file_name_size);
			queue_enq((struct LIST *)file_entry, &FILE_LIST_HEAD);
		}
	}

	ST->ConOut->ClearScreen(ST->ConOut);
	puts(L"\r\n", ST);
	for (file_entry = (struct FILE_LIST *)FILE_LIST_HEAD.next; FILE_LIST_HEAD.next != &FILE_LIST_HEAD;
	     file_entry = (struct FILE_LIST *)file_entry->list.next) {
		puts(L"  ", ST);
		puts(file_entry->name, ST);

		if (file_entry->list.next == &FILE_LIST_HEAD)
			break;
	}

	unsigned int start_x = FILE_RECT_START_X;
	unsigned int start_y = FILE_RECT_START_Y;
	unsigned int file_rect_width;
	for (file_entry = (struct FILE_LIST *)FILE_LIST_HEAD.next; FILE_LIST_HEAD.next != &FILE_LIST_HEAD;
	     file_entry = (struct FILE_LIST *)file_entry->list.next) {
		file_rect_width =
			((unsigned int)strlen(file_entry->name) - 1) * RECT_WIDTH_PER_CH;
		file_entry->rect.x = start_x;
		file_entry->rect.y = start_y;
		file_entry->rect.width = file_rect_width;
		file_entry->rect.height = FILE_RECT_HEIGHT;
		draw_rect(file_entry->rect.x, file_entry->rect.y,
			  file_entry->rect.width, file_entry->rect.height, GOP);
		start_x += file_rect_width + FILE_MARGIN_WIDTH;

		if (file_entry->list.next == &FILE_LIST_HEAD)
			break;
	}

	status = root->Close(root);
	check_status(status, L"Close", ST);
}

void poll_mouse_pointer(void)
{
	unsigned long long status;
	struct EFI_SIMPLE_POINTER_STATE sps;
	int x = 0;
	int y = 0;
	unsigned char is_first = 1;
	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL tmp[4];

	status = SPP->Reset(SPP, FALSE);
	check_status(status, L"Reset(SPP)", ST);

	while (1) {
		status = SPP->GetState(SPP, &sps);
		if (!status) {
			if (!is_first) {
				draw_pixel(x, y, tmp[0], GOP);
				draw_pixel(x + 1, y, tmp[1], GOP);
				draw_pixel(x, y + 1, tmp[2], GOP);
				draw_pixel(x + 1, y + 1, tmp[3], GOP);
			} else {
				is_first = 0;
			}
			x += sps.RelativeMovementX >> 13;
			if (x < 0)
				x = 0;
			y += sps.RelativeMovementY >> 13;
			if (y < 0)
				y = 0;
			tmp[0] = get_pixel(x, y);
			tmp[1] = get_pixel(x + 1, y);
			tmp[2] = get_pixel(x, y + 1);
			tmp[3] = get_pixel(x + 1, y + 1);
			draw_rect(x, y, 2, 2, GOP);
		}
	}
}

void efi_main(void *ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable)
{
	init_protocols(ImageHandle, SystemTable);
	queue_init(&FILE_LIST_HEAD);

	draw_file_list();

	poll_mouse_pointer();

	while (1);
}
