# ClipShadow: Steganographic C++ Windows Payload

> **Academic Research Project** - Master's Thesis in Cybersecurity  
> *Advanced Post-Exploitation Techniques & Covert Communication Systems*

This repository contains a Windows-targeting C++ clipboard intercepting payload developed as part of a cybersecurity Master's dissertation. The project demonstrates advanced attack techniques including steganographic configuration storage, cryptographic obfuscation, persistence mechanisms, and covert data exfiltration.

> ⚠️ **ACADEMIC USE ONLY** - This tool is designed exclusively for cybersecurity research, education, and controlled penetration testing environments. Use only on systems you own or have explicit authorization to test.

---

## 🎯 Project Overview

**ClipShadow** is a proof-of-concept advanced persistent threat (APT) simulation that demonstrates sophisticated malware techniques used in real-world cyber attacks. The project showcases the intersection of cryptography, steganography, and system-level programming in the context of offensive cybersecurity research.

### 🔬 Academic Significance

This project serves as the technical foundation for exploring:
- **Covert Communication Channels** in legitimate file formats
- **Advanced Cryptographic Obfuscation** for configuration protection  
- **Memory-Safe Cryptographic Implementation** in native code
- **Evasion Techniques** against traditional malware detection
- **Post-Exploitation Data Harvesting** methodologies

---

## 🛡️ Implemented Security Techniques

### 🔐 **Cryptographic Systems**
- **AES-256-CBC Encryption** with proper IV handling and PKCS#7 padding
- **Secure Key Management** with memory clearing after use
- **Multi-field Encryption** with individual initialization vectors
- **Compile-time String Obfuscation** using XOR with FNV-1a hashing

### 🎵 **Steganographic Implementation**
- **LSB Audio Steganography** in WAV files for configuration storage
- **Capacity Analysis** and optimal data embedding techniques
- **Integrity Verification** for extracted steganographic payloads
- **Format-Preserving Embedding** maintaining audio file validity

### 🔧 **System-Level Operations**
- **Windows Registry Manipulation** for persistence establishment
- **Clipboard API Integration** for real-time data monitoring
- **WinINet HTTP Communications** for covert data exfiltration
- **Memory Management** with secure data clearing practices

### 🕵️ **Anti-Analysis Features**
- **Static String Obfuscation** preventing signature-based detection
- **Minimal Import Table** through static linking
- **Registry-Based Persistence** mimicking legitimate system services
- **Error-Resistant Communication** with graceful failure handling

---

## 🏗️ Architecture & Design

### **Core Components**

```
📁 ClipShadow/
├── 🎵 Steganographic Config System
│   ├── WAV file format manipulation
│   ├── LSB data embedding/extraction
│   └── Audio integrity preservation
│
├── 🔐 Cryptographic Engine
│   ├── AES-256-CBC implementation
│   ├── PKCS#7 padding handling
│   ├── Secure memory management
│   └── Multi-field encryption
│
├── 📋 Data Harvesting Module
│   ├── Real-time clipboard monitoring
│   ├── Unicode text extraction
│   ├── Change detection algorithms
│   └── Data deduplication
│
├── 🌐 Covert Communication
│   ├── HTTP/HTTPS exfiltration
│   ├── Configurable endpoints
│   ├── Error handling & retry logic
│   └── Traffic obfuscation
│
└── 🔧 Persistence Framework
    ├── Windows Registry modification
    ├── Startup approval handling
    ├── Service name obfuscation
    └── Privilege escalation awareness
```

### **Data Flow Architecture**

```
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│   WAV File      │───▶│  LSB Extraction  │───▶│  Encrypted      │
│  (ouch.wav)     │    │  (Steganography) │    │  Config Blob    │
└─────────────────┘    └──────────────────┘    └─────────────────┘
                                                        │
                                                        ▼
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│  Final Config   │◄───│  AES-256-CBC     │◄───│  Blob Parsing   │
│  (Host/Port)    │    │  Decryption      │    │  (Key/IV/Data)  │
└─────────────────┘    └──────────────────┘    └─────────────────┘
         │
         ▼
┌─────────────────┐    ┌──────────────────┐    ┌─────────────────┐
│  HTTP POST      │◄───│  Clipboard Data  │◄───│  Real-time      │
│  Exfiltration   │    │  Processing      │    │  Monitoring     │
└─────────────────┘    └──────────────────┘    └─────────────────┘
```

---

## 🚀 Advanced Features

### ✅ **Implemented Capabilities**

- [x] **Multi-layer Configuration Obfuscation**
  - Steganographic storage in audio files
  - AES-256-CBC encryption with unique IVs
  - Structured binary format parsing

- [x] **Real-time Data Harvesting**
  - Clipboard content monitoring
  - Unicode text processing
  - Duplicate detection and filtering

- [x] **Covert Network Communication**
  - HTTP/HTTPS data exfiltration
  - Configurable C2 infrastructure
  - Form-encoded payload transmission

- [x] **Advanced Persistence Mechanisms**
  - Registry-based auto-startup
  - Windows startup approval bypass
  - Service name obfuscation

- [x] **Anti-Analysis Countermeasures**
  - Compile-time string encryption
  - Static binary compilation
  - Minimal API surface exposure

- [x] **Memory Security Implementation**
  - Secure key material clearing
  - Buffer overflow protections
  - Controlled memory allocation

---

## 🛠️ Technical Implementation

### **Build System**
```bash
# Native Windows compilation with MinGW-w64
g++ -Wall -O0 -g -Iheaders -static -mwindows \
    src/main.cpp src/aes.c src/clipboard.cpp \
    src/tools.cpp src/httpexfil.cpp src/wavcrypt.cpp \
    -o svchost_monitor.exe -lwininet
```

### **Development Environment**
- **Language**: C++17 with Windows API integration
- **Compiler**: MinGW-w64 for cross-platform development
- **Cryptography**: Custom AES implementation with CBC mode
- **Build Tools**: VS Code with integrated debugging support

### **Dependencies**
- **WinAPI**: Core Windows system integration
- **WinINet**: HTTP communication libraries
- **Custom AES**: Embedded cryptographic implementation
- **STL**: Modern C++ standard library features

---

## 🎓 Academic Contributions

### **Research Areas Addressed**

1. **Steganographic Communication Channels**
   - Analysis of LSB techniques in audio formats
   - Capacity vs. detectability trade-offs
   - Format-preserving data embedding

2. **Applied Cryptography in Malware**
   - Secure configuration storage mechanisms
   - Key management in adversarial environments
   - Performance optimization for embedded crypto

3. **Windows Internals Exploitation**
   - Registry-based persistence techniques
   - Clipboard API abuse vectors
   - Memory management in hostile environments

4. **Network Covert Channels**
   - HTTP protocol abuse for data exfiltration
   - Traffic pattern obfuscation techniques
   - Resilient communication protocols

### **Novel Contributions**

- **Integrated Steganographic Framework** combining audio steganography with advanced encryption
- **Memory-Safe Malware Architecture** demonstrating secure coding practices in offensive tools
- **Cross-Platform Development Methodology** for Windows malware research
- **Academic Logging Framework** for educational demonstration and analysis

---

## � Defensive Research Implications

This research provides valuable insights for defensive cybersecurity:

- **Detection Signatures** for steganographic malware variants
- **Behavioral Analysis Patterns** for clipboard-based data theft
- **Registry Monitoring** for persistence detection
- **Network Traffic Analysis** for covert channel identification

---

## 📚 Academic Applications

### **Cybersecurity Education**
- Hands-on malware analysis training
- Cryptographic implementation studies
- Windows internals exploration
- Incident response scenario development

### **Research Extensions**
- Machine learning detection algorithms
- Advanced steganographic techniques
- Network forensics methodologies
- Behavioral malware analysis

---

## 🏆 Professional Relevance

This project demonstrates proficiency in:

- **Advanced C++ Programming** with Windows API integration
- **Applied Cryptography** implementation and best practices  
- **Reverse Engineering** and malware analysis techniques
- **Network Security** protocols and covert communications
- **System Administration** and Windows internals knowledge
- **Security Research** methodology and documentation

---

## ⚖️ Ethical Guidelines

This research adheres to responsible disclosure principles and academic ethical standards:

- **Controlled Environment**: All testing conducted in isolated lab environments
- **Educational Purpose**: Designed for cybersecurity education and defense research
- **No Malicious Intent**: Created solely for academic and defensive security purposes
- **Responsible Sharing**: Source code available only for legitimate research purposes

---


This software is provided for educational use only. Do **not** deploy it on systems you do not own or have explicit permission to test. The author is not responsible for any misuse.