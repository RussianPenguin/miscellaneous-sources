#include <windows.h>
#define UNICODE
#pragma comment(lib,"user32.lib")

typedef BOOL WINAPI CreateProcessWithLogonW(
 LPCWSTR lpUsername,                 // user's name
 LPCWSTR lpDomain,                   // user's domain
 LPCWSTR lpPassword,                 // user's password
 DWORD dwLogonFlags,                 // logon option
 LPCWSTR lpApplicationName,          // executable module name
 LPWSTR lpCommandLine,               // command-line string
 DWORD dwCreationFlags,              // creation flags
 LPVOID lpEnvironment,               // new environment block
 LPCWSTR lpCurrentDirectory,         // current directory name
 LPSTARTUPINFOW lpStartupInfo,       // startup information
 LPPROCESS_INFORMATION lpProcessInfo // process information
);

int main(void)
{
 char err[256];
 HANDLE hToken, A;
 STARTUPINFOW si = {sizeof(STARTUPINFOW)};
 PROCESS_INFORMATION pi;
 FARPROC W;     
 wchar_t *pName = L"cmd.exe";
 wchar_t *aName = L"S7a1k3r";
 wchar_t *aPassw = L"gbplf";
 wchar_t *aSrv = L"";
 BOOL rez;

 HINSTANCE Hlib = LoadLibrary("advapi32.dll");
 if(!Hlib){
         MessageBox(0,"Lib error","!",0);
         return 0;
 }
 W = GetProcAddress(Hlib,"CreateProcessWithLogonW");

 rez = ((CreateProcessWithLogonW*)W)(aName,aSrv,aPassw,1, 
         pName,pName,0,NULL,NULL,&si, &pi);
 if(rez == 0){
      wsprintf(err, "Error [%ld] creating process!", GetLastError());
      MessageBox(0, err, "Error", 0);
 }
 return 0;
}

