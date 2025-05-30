
#pragma once
#include <array>
#include <cstdint>
#include <utility>

// Compile-time FNV-1a hash (seed variation for per-string obfuscation)
constexpr uint32_t fnv1a(const char* s, std::size_t count, uint32_t hash = 2166136261u) {
    return count ? fnv1a(s + 1, count - 1, (hash ^ static_cast<uint32_t>(*s)) * 16777619u) : hash;
}

template <std::size_t N, uint32_t Key>
class ObfStr {
    std::array<char, N> data{};

    static constexpr char encode(char c, std::size_t i) {
        return c ^ static_cast<char>((Key + i) & 0xFF);
    }

public:
    constexpr ObfStr(const char (&str)[N]) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = encode(str[i], i);
        }
    }

    const char* decrypt() {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = encode(data[i], i); // XOR back
        }
        return data.data();
    }
};

#define OBFSTR(str) \
    ([] { \
        constexpr auto key = fnv1a(str, sizeof(str)); \
        static ObfStr<sizeof(str), key> obf{str}; \
        return obf.decrypt(); \
    }())
