#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <cstdint>

std::string WStringToUtf8(const std::wstring& wstr);
void AddToStartup();
void PrintHexData(const std::string& label, const std::vector<uint8_t>& data, size_t maxBytes = 32);