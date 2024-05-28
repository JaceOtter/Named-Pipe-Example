#include <Windows.h>
#include <iostream>
using namespace std;
int main()
{
    cout << "\t\t....NAMED PIPE SERVER" << endl;

    // Named Pipe Local Variable
    HANDLE      hCreateNamedPipe;
    char        szInputBuffer[1023];
    char        szOutputBuffer[1023];
    DWORD       dwInputBuffer = sizeof(szInputBuffer);
    DWORD       dwOutputBuffer = sizeof(szOutputBuffer);

    // Connect Named Pipe Local Variable
    BOOL        bConnectNamedPipe;

    // WriteFile Local Variable
    BOOL        bWriteFile;
    char        szWriteFileBuffer[1023] = "Hello From NamedPipe Server!!";
    DWORD       dwWriteBufferSize = sizeof(szWriteFileBuffer);
    DWORD       dwNoBytesWrite;

    // Flush Buffer Variable
    BOOL        bFlushFileBuffer;

    // ReadFile Local Variable
    BOOL        bReadFile;
    char        szReadFileBuffer[1023];
    DWORD       dwReadBufferSize = sizeof(szReadFileBuffer);
    DWORD       dwNoBytesRead;


    // Create Named Pipe - STEP 1

    hCreateNamedPipe = CreateNamedPipe(
        L"\\\\.\\pipe\\MYNAMEDPIPE",
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        dwOutputBuffer,
        dwInputBuffer,
        0,
        NULL);
    if (hCreateNamedPipe == INVALID_HANDLE_VALUE)
        cout << "CreateNamedPipe Failed with Error No - " << GetLastError() << endl;
    else
        cout << "CreateNamedPipe Success" << endl;


    // Connect Named Pipe - STEP 2

    bConnectNamedPipe = ConnectNamedPipe(hCreateNamedPipe, NULL);
    if (bConnectNamedPipe == FALSE)
        cout << "ConnectNamedPipe Failed with ErrorNo - " << GetLastError() << endl;
    else
        cout << "ConnectNamedPipe Succeeded" << endl;


    // WriteFile Operation - STEP 3

    bWriteFile = WriteFile(
        hCreateNamedPipe,
        szWriteFileBuffer,
        dwWriteBufferSize,
        &dwNoBytesWrite,
        NULL);

    if (bWriteFile == FALSE)
        cout << "WriteFile Failed with Error No - " << GetLastError() << endl;
    else
        cout << "WriteFile Succeeded" << endl;


    // Flush the File Buffer - STEP 4

    bFlushFileBuffer = FlushFileBuffers(hCreateNamedPipe);
    if (bFlushFileBuffer == FALSE)
        cout << "FlushFileBuffers Failed with Error No - " << GetLastError() << endl;
    else
        cout << "FlushFileBuffers Succeeded" << endl;


    // ReadFile - STEP 5

    bReadFile = ReadFile(
        hCreateNamedPipe,
        szReadFileBuffer,
        dwReadBufferSize,
        &dwNoBytesRead,
        NULL);

    if (bReadFile == FALSE)
        cout << "ReadFile Failed with Error No - " << GetLastError() << endl;
    else
        cout << "ReadFile Succeeded" << endl;

    cout << "Data Read from Client -> " << szReadFileBuffer << endl;


    // Disconnect Named Pipe - STEP 6

    DisconnectNamedPipe(hCreateNamedPipe);


    // Close Handle - STEP 7

    CloseHandle(hCreateNamedPipe);
}
