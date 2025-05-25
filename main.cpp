#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

std::string GetClipboardText()
{
    if(!OpenClipboard(nullptr))
    {
        return "Failed. Clipboard is not open.";
    }

    HANDLE hData = GetClipboardData(CF_TEXT);

    char* textArray = static_cast<char*>(GlobalLock(hData));
    if(textArray == nullptr)
    {
        CloseClipboard();
        return "Failed. Cannot lock clipboard memory location.";
    }

    std::string text(textArray);

    GlobalUnlock(hData);
    CloseClipboard();

    return text;
}


int main() {
    std::cout << "[*] Clipboard Interceptor Started\n";
    std::string lastClipboard = "";

    while(true)
    {
        std::string currentClipboard = GetClipboardText();

        if(!currentClipboard.empty() && currentClipboard != lastClipboard) {
            std::cout << "[*] New Clipboard Content:\n\n" << currentClipboard << "\n\n";
            lastClipboard = currentClipboard;
        }

        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
