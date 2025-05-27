import wave
import re

# === Step 1: Load embedded_config from config_blob.h ===
with open("crypt/config_blob.h", "r") as f:
    content = f.read()

# Extract all hex bytes: 0xAB, etc.
byte_values = [int(x, 16) for x in re.findall(r"0x([0-9A-Fa-f]{2})", content)]
bitstream = []
for byte in byte_values:
    for i in range(8):
        bit = (byte >> (7 - i)) & 1  # MSB-first
        bitstream.append(bit)

# === Step 2: Open the base WAV ===
with wave.open("crypt/ouch.wav", "rb") as wav:
    params = wav.getparams()
    assert params.sampwidth == 2, "Only 16-bit WAV files are supported."
    assert params.nchannels in [1, 2], "Mono or stereo only."
    samples = bytearray(wav.readframes(wav.getnframes()))

num_samples = len(samples) // 2
if len(bitstream) > num_samples:
    raise ValueError("WAV file too short to hold the config data.")

# === Step 3: Embed bits into LSBs of each 16-bit sample ===
for i, bit in enumerate(bitstream):
    sample_index = i * 2
    samples[sample_index] = (samples[sample_index] & 0xFE) | bit  # overwrite LSB

# === Step 4: Write to stego.wav ===
with wave.open("stego.wav", "wb") as out:
    out.setparams(params)
    out.writeframes(samples)

"✅ Embedding complete. stego.wav now contains the AES-encrypted config in LSBs."
