# Clipboard Interceptor Payload (C++ / Windows)

This repository contains the development of a custom Windows clipboard interception payload, written in C++. The goal of this project is to build a realistic, stealthy, and extensible post-exploitation tool suitable for academic research and cybersecurity training.

> ⚠️ This tool is for **educational and research purposes only**. Use it only in controlled lab environments on systems you own or are authorized to test.

---

## 🚧 Project Status

**IN DEVELOPMENT** — Currently working on v1 prototype. Functionality is minimal and focused on clipboard monitoring only. Advanced features like exfiltration and persistence will follow.

---

## 📦 Features (Current v1)

- [x] Native Windows C++ binary
- [x] Uses WinAPI to access clipboard (`OpenClipboard`, `GetClipboardData`, etc.)
- [x] Polls every X seconds (configurable)
- [x] Detects and logs clipboard changes

---

## 📋 Roadmap / To-Do

## 🔹 Core Clipboard Functionality
- [x] Poll clipboard for text
- [x] Detect changes and avoid duplicate logs

## 🔹 Encrypted HTTPS Exfiltration
- [x] Parse config (host, port, path) from `.wav` via LSB
- [x] Extract and decode AES key from `.wav`
- [x] Decrypt configuration
- [x] Convert clipboard data to UTF-8
- [x] Migrate HTTP to **HTTPS** (via WinHTTP or adjusted WinINet)
- [ ] Encrypt clipboard data before sending

## 🔹 Stealth & Evasion
- [x] Hide console window - compile with -mwindows
- [x] Add persistence via Windows Registry (`HKCU\...\Run`)
- [x] Static build (no DLL dependencies)
- [x] Encrypt all static strings (XOR or compile-time)
- [ ] Add randomized delays to mimic human behavior
- [ ] Minimize binary footprint (optional UPX, etc.)
- [x] Obfuscate generated machine code

---

## 🛠 Build Instructions (Cross-compile on Kali Linux)

```bash
sudo apt install mingw-w64
x86_64-w64-mingw32-g++ main.cpp -o clipwatcher.exe -static
```

Then test the `clipwatcher.exe` inside a Windows 10/11 VM.

---

## 🔬 Academic Relevance

This project is the technical core of a cybersecurity Master's thesis, focusing on stealthy post-exploitation payload design. It explores topics such as clipboard data harvesting, covert exfiltration, anti-analysis, persistence, and evasion — all grounded in practical attacker techniques and defensive bypass analysis.

---

## 🧠 Disclaimer

This software is provided for educational use only. Do **not** deploy it on systems you do not own or have explicit permission to test. The author is not responsible for any misuse.
