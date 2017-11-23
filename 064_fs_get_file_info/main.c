#include <efi.h>
#include <common.h>

#define FILE_INFO_BUF_SIZE	128
unsigned char fi_buf[FILE_INFO_BUF_SIZE];

void efi_main(void *ImageHandle __attribute__ ((unused)),
	      struct EFI_SYSTEM_TABLE *SystemTable)
{
	unsigned long long status;
	struct EFI_FILE_PROTOCOL *root;
	struct EFI_FILE_PROTOCOL *file;
	unsigned long long fi_size = FILE_INFO_BUF_SIZE;
	struct EFI_FILE_INFO *fi_ptr;

	efi_init(SystemTable);

	status = SFSP->OpenVolume(SFSP, &root);
	assert(status, L"SFSP->OpenVolume");

	status = root->Open(root, &file, L"foo.dat", EFI_FILE_MODE_READ, 0);
	assert(status, L"root->Open");

	status = file->GetInfo(file, &fi_guid, &fi_size, (void *)&fi_buf);
	assert(status, L"file->GetInfo");

	puts(L"sizeof(struct EFI_FILE_INFO) = 0x");
	puth(sizeof(struct EFI_FILE_INFO), 16);
	puts(L"\r\n");

	puts(L"fi_size = 0x");
	puth(fi_size, 16);
	puts(L"\r\n");

	fi_ptr = (struct EFI_FILE_INFO *)&fi_buf;
	puts(L"fi_ptr = 0x");
	puth((unsigned long long)fi_ptr, 16);
	puts(L"\r\n");
	puts(L"&fi_ptr->Attribute = 0x");
	puth((unsigned long long)&fi_ptr->Attribute, 16);
	puts(L"\r\n");

	puts(L"fi_ptr->Size = 0x");
	puth(fi_ptr->Size, 16);
	puts(L"\r\n");
	puts(L"fi_ptr->FileSize = 0x");
	puth(fi_ptr->FileSize, 16);
	puts(L"\r\n");
	puts(L"fi_ptr->PhysicalSize = 0x");
	puth(fi_ptr->PhysicalSize, 16);
	puts(L"\r\n");

	file->Close(file);
	root->Close(root);

	while (TRUE);
}
