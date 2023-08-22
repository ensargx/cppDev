#pragma once

#include <Windows.h>

class Memory
{
public:
    Memory(const char* processName);
    ~Memory();

    DWORD GetProcessId();
    HANDLE GetProcessHandle();

    uintptr_t GetModuleAddress(const char* moduleName);

    template<typename T> 
    T Read(uintptr_t address)
    {
        T value;
        ReadProcessMemory(this->process, (LPCVOID)address, &value, sizeof(T), NULL);
        return value;
    }

    template<typename T>
    bool Write(uintptr_t address, T value)
    {
        return WriteProcessMemory(this->process, (LPVOID)address, &value, sizeof(T), NULL);
    }

private:
    DWORD id = 0;          // id of the process
    HANDLE process = NULL; // handle to the process
};
