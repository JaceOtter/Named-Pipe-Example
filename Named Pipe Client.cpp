#include <Windows.h>
#include <iostream>
using namespace std;
int main()
{
    cout << "\t\t....NAMED PIPE CLIENT" << endl;

    // Named Pipe Local Variable
    HANDLE      hCreateFile;
 //   char        szInputBuffer[1023];
 //   char        szOutputBuffer[1023];
 //   DWORD       dwInputBuffer = sizeof(szInputBuffer);
 //   DWORD       dwOutputBuffer = sizeof(szOutputBuffer);

    // Connect Named Pipe Local Variable
 //   BOOL        bConnectNamedPipe;

    // WriteFile Local Variable
    BOOL        bWriteFile;
    char        szWriteFileBuffer[1023] = "Hello From NamedPipe Client!!";
    DWORD       dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD       dwNoBytesWrite;

    // Flush Buffer Variable
 //   BOOL        bFlushFileBuffer;

    // ReadFile Local Variable
    BOOL        bReadFile;
    char        szReadFileBuffer[1023];
    DWORD       dwReadBufferSize = sizeof(szReadFileBuffer);
    DWORD       dwNoBytesRead;
 

    // Create File for Pipe - STEP 1

    hCreateFile = CreateFile(
        L"\\\\.\\pipe\\MYNAMEDPIPE",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL);
    if (hCreateFile == INVALID_HANDLE_VALUE)
        cout << "CreateFile Failed with Error No - " << GetLastError() << endl;
    else
        cout << "CreateFile Success" << endl;


    // ReadFile - STEP 2

    bReadFile = ReadFile(
        hCreateFile,
        szReadFileBuffer,
        dwReadBufferSize,
        &dwNoBytesRead,
        NULL);

    if (bReadFile == FALSE)
        cout << "ReadFile Failed with Error No - " << GetLastError() << endl;
    else
        cout << "ReadFile Succeeded" << endl;

    cout << "Data Read from Server -> " << szReadFileBuffer << endl;


    // WriteFile Operation - STEP 3

    bWriteFile = WriteFile(
        hCreateFile,
        szWriteFileBuffer,
        dwWriteBufferSize,
        &dwNoBytesWrite,
        NULL);

    if (bWriteFile == FALSE)
        cout << "WriteFile Failed with Error No - " << GetLastError() << endl;
    else
        cout << "WriteFile Succeeded" << endl;

    CloseHandle(hCreateFile);
    system("PAUSE");

    return(0);
}
