#include <iostream>
#include<fstream>
#include<windows.h>

using namespace std;

int main(int argc, char *argv[])
{

    char mass[256];
    char file_name[] = "test.txt";
    HANDLE hFile, hMapping;
    char* ptr;

    hFile = CreateFile(file_name, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        cerr << "Create file failed." << endl;
        return GetLastError();
    }

    hMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (!hMapping)
    {
        cerr << "Create file mapping failed." << endl;
        return GetLastError();
    }

    ptr = (char*)MapViewOfFile(hMapping, FILE_MAP_WRITE, 0, 0, 0);


    for (int i = 0; i < 256; ++i)
    {
        if (ptr[i] == *argv[1])
        {
            ptr[i] = *argv[2];
        }
    }

    if (!UnmapViewOfFile(ptr))
    {
        cerr << "Unmap viev of file failed." << endl;
        return GetLastError();
    }

    if (!CloseHandle(hMapping))
    {
        cerr << "Close file failed." << endl;
        return GetLastError();
    }

    if (!CloseHandle(hFile))
    {
        cerr << "Close file failed." << endl;
        return GetLastError();
    }


    ifstream in(file_name, ios::in, ios::binary);
    if (!in)
    {
        cerr << "File constructor failed." << endl;
        return 0;
    }

    cout << "Final array: ";
    for (int i = 0; i < 256; ++i)
    {
        in.read((char*)&mass[i], sizeof(char));

        char ch = mass[i];

        if (mass[i] != -52)
        {
            cout << mass[i];
        }
    }
    cout << endl;

    return 0;
}