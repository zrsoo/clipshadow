#include <string>
#include <windows.h>

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