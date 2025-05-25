#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

#include <clipboard.h>
#include <tools.h>

// Console ouput UTF_16 format, TODO REMOVE
#include <fcntl.h>
#include <io.h>

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
