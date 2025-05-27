import wave
import re

# === Load original embedded_config[] for comparison ===
with open("crypt/config_blob.h", "r") as f:
    content = f.read()

original_bytes = [int(x, 16) for x in re.findall(r"0x([0-9A-Fa-f]{2})", content)]
num_bits = len(original_bytes) * 8

# === Read stego.wav and extract LSBs ===
with wave.open("ouch.wav", "rb") as wav:
    samples = bytearray(wav.readframes(wav.getnframes()))

# Rebuild bitstream from LSBs
bitstream = []
for i in range(num_bits):
    sample_index = i * 2
    bit = samples[sample_index] & 0x01
    bitstream.append(bit)

# Convert bitstream back to bytes
extracted_bytes = bytearray()
for i in range(0, len(bitstream), 8):
    byte = 0
    for bit in bitstream[i:i+8]:
        byte = (byte << 1) | bit
    extracted_bytes.append(byte)

# === Compare with original ===
match = extracted_bytes == bytearray(original_bytes)

print("✅ Match!" if match else "❌ Mismatch!")
if not match:
    print("Extracted (first 32 bytes):", extracted_bytes[:32])
    print("Original  (first 32 bytes):", original_bytes[:32])
