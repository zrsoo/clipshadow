#pragma once
#include <cstdint>
#include <vector>
#include <tuple>
#include <string>

std::vector<uint8_t> ExtractEmbeddedConfigFromWav(const std::string& filepath);
std::tuple<std::string, std::string, std::string> ExtractAndDecryptConfig(const std::string& filepath);
std::string DecryptAES256CBC(const std::vector<uint8_t>& ciphertext, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv);