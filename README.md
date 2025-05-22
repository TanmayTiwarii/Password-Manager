# 🔐 C++ Password Manager with RSA Encryption (No External Libraries)

This is a simple password manager written in C++ that:
- Uses **RSA encryption** (implemented from scratch, no external libraries)
- Stores encrypted passwords associated with websites and usernames
- Requires a master password (`Tanmay12345`) to access the system
- Supports saving/loading entries to a file
- Lets you search passwords by website name

---

## 🛠️ Features

- 🔑 **Master password protection**
- 🔒 **RSA encryption** for stored passwords
- 💾 **Persistent storage** in `vault_rsa.dat`
- 👁️‍🗨️ **View and search credentials** by website
- 📜 Fully written in **pure C++**, no dependencies

---

## 📂 Project Structure

```
password-manager/
├── main.cpp         # All implementation in a single file
├── vault_rsa.dat    # Auto-created on first save; stores encrypted entries
└── README.md
```

---

## 🧪 Example Usage

```bash
$ g++ -o password_manager main.cpp
$ ./password_manager
```

Then, follow the prompts:
```
Enter access password: Tanmay12345

1. Add Entry
2. List Entries
3. Search by Website
4. Save and Exit
Choose an option:
```

---

## 🔐 How RSA Is Implemented

- Small prime numbers (`p = 61`, `q = 53`) for demo purposes
- Manual generation of public (`e`) and private (`d`) keys
- Basic modular exponentiation (`modPow`) used for encryption/decryption
- Passwords are encrypted character by character into numbers

*Note: This is a simplified version of RSA meant for educational purposes only and is not secure for real-world use.*

---

## 📌 Limitations & Notes

- The RSA implementation is **not secure for production use**
- The master password is **hardcoded** (`Tanmay12345`)
- Passwords are stored encrypted, but the master password is not
- Entries are stored in plaintext file with encrypted fields

---

## ✅ To-Do / Improvements

- Store RSA keys in a separate file
- Use cryptographically secure key sizes and randomness
- Add ability to **update** or **delete** entries
- Support **partial keyword search**
- Replace hardcoded master password with a hashed version

---

## 📄 License

This project is for educational purposes and is provided as-is with no warranty. You are free to modify and use it for your own learning or demo projects.
