#define MAX_LINE_SIZE	512

enum {
	ECHO,
#ifdef DEBUG
	TEST,
#endif /* DEBUG */
	COMMAND_NUM
} _COMMAND_SET;

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

struct EFI_SYSTEM_TABLE *SystemTable;

static void str_copy(const unsigned short *src, unsigned short *dst, unsigned int size)
{
	for (; size > 0; size--)
		*dst++ = *src++;
}

static void put_char(unsigned short c)
{
	unsigned short str[2] = L" ";

	str[0] = c;
	SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
}

static void put_str(unsigned short *str)
{
	SystemTable->ConOut->OutputString(SystemTable->ConOut, str);
}

static unsigned short get_char(void)
{
	struct EFI_INPUT_KEY efi_input_key;

	while (SystemTable->ConIn->ReadKeyStroke(SystemTable->ConIn, &efi_input_key));

	return efi_input_key.UnicodeChar;
}

static unsigned int get_line(unsigned short *buf, unsigned int buf_size)
{
	unsigned int i;

	for (i = 0; i < buf_size - 1;) {
		buf[i] = get_char();
		put_char(buf[i]);
		if (buf[i] == L'\r') {
			put_char(L'\n');
			break;
		}
		i++;
	}
	buf[i] = L'\0';

	return i;
}

static int str_get_len(const unsigned short *src)
{
	int len;
	for (len = 0; src[len] != L'\0'; len++);
	return len + 1;
}

int str_find_char(const unsigned short *src, unsigned short key)
{
	int i;

	for (i = 0; src[i] != key; i++) {
		if (src[i] == L'\0') {
			i = -1;
			break;
		}
	}

	return i;
}

static void str_get_first_entry(const unsigned short *line, unsigned short *first, unsigned short *other)
{
	int line_len, first_len, other_len;

	line_len = str_get_len(line);
	first_len = str_find_char(line, L' ');
	if (first_len < 0) {
		str_copy(line, first, line_len);
		first_len = line_len;
		other_len = 0;
		other[other_len] = L'\0';
	} else {
		str_copy(line, first, first_len);
		first[first_len] = L'\0';
		first_len++;
		other_len = line_len - first_len;
		str_copy(line + first_len, other, other_len);
	}
}

static int str_compare(const unsigned short *src, const unsigned short *dst)
{
	char is_equal = 1;

	for (; (*src != L'\0') && (*dst != L'\0'); src++, dst++) {
		if (*src != *dst) {
			is_equal = 0;
			break;
		}
	}

	if (is_equal) {
		if (*src != L'\0') {
			return 1;
		} else if (*dst != L'\0') {
			return -1;
		} else {
			return 0;
		}
	} else {
		return (int)(*src - *dst);
	}
}

static int command_echo(unsigned short *args)
{
	put_str(args);
	put_str(L"\r\n");

	return 0;
}

#ifdef DEBUG
static int command_test(unsigned short *args __attribute__ ((unused)))
{
	put_str(L"test\r\n");

	return 0;
}
#endif /* DEBUG */

static unsigned char get_command_id(const unsigned short *command)
{
	if (!str_compare(command, L"echo")) {
		return ECHO;
	}

#ifdef DEBUG
	if (!str_compare(command, L"test")) {
		return TEST;
	}
#endif /* DEBUG */

	return COMMAND_NUM;
}

void shell(void)
{
	unsigned short buf[MAX_LINE_SIZE];
	unsigned short command[256], args[256];
	unsigned char command_id;

	while (1) {
		put_str(L"shell> ");
		if (get_line(buf, MAX_LINE_SIZE) <= 0) {
			continue;
		}

		str_get_first_entry(buf, command, args);
		command_id = get_command_id(command);

		switch (command_id) {
		case ECHO:
			command_echo(args);
			break;
#ifdef DEBUG
		case TEST:
			command_test(args);
			break;
#endif /* DEBUG */
		default:
			put_str(L"Command not found.\r\n");
			break;
		}
	}
}

void efi_main(void *ImageHandle __attribute__ ((unused)), struct EFI_SYSTEM_TABLE *_SystemTable)
{
	SystemTable = _SystemTable;
	shell();
}
