// Password Manager in C++ using RSA encryption (no external libraries)
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void generateRSAKeys(long long& e, long long& d, long long& n) {
    // Small demo primes (for real use, use large primes and a crypto library)
    long long p = 61;
    long long q = 53;
    n = p * q;
    long long phi = (p - 1) * (q - 1);
    e = 17;
    while (gcd(e, phi) != 1) e++;
    long long k = 1;
    while ((k * phi + 1) % e != 0) k++;
    d = (k * phi + 1) / e;
}

string rsaEncrypt(const string& msg, long long e, long long n) {
    string cipher;
    for (char c : msg) {
        long long enc = modPow((long long)c, e, n);
        cipher += to_string(enc) + " ";
    }
    return cipher;
}

string rsaDecrypt(const string& cipher, long long d, long long n) {
    string msg;
    size_t pos = 0, next;
    while ((next = cipher.find(' ', pos)) != string::npos) {
        long long enc = stoll(cipher.substr(pos, next - pos));
        char dec = (char)modPow(enc, d, n);
        msg += dec;
        pos = next + 1;
    }
    return msg;
}

struct Entry {
    string website;
    string username;
    string encryptedPassword;
};

class PasswordManager {
public:
    PasswordManager() {
        generateRSAKeys(e, d, n);
    }

    void addEntry(const string& website, const string& username, const string& password) {
        Entry entry;
        entry.website = website;
        entry.username = username;
        entry.encryptedPassword = rsaEncrypt(password, e, n);
        entries.push_back(entry);
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (const auto& e : entries) {
            file << e.website << '\t' << e.username << '\t' << e.encryptedPassword << '\n';
        }
        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        string line;
        while (getline(file, line)) {
            Entry entry;
            size_t pos1 = line.find('\t');
            size_t pos2 = line.rfind('\t');
            if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) continue;
            entry.website = line.substr(0, pos1);
            entry.username = line.substr(pos1 + 1, pos2 - pos1 - 1);
            entry.encryptedPassword = line.substr(pos2 + 1);
            entries.push_back(entry);
        }
        file.close();
    }

    void listEntries() {
        for (const auto& e : entries) {
            cout << "Website: " << e.website << ", Username: " << e.username
                 << ", Password: " << rsaDecrypt(e.encryptedPassword, d, n) << endl;
        }
    }

    void getEntryByWebsite(const string& website) {
        bool found = false;
        for (const auto& e : entries) {
            if (e.website == website) {
                cout << "Website: " << e.website << ", Username: " << e.username
                     << ", Password: " << rsaDecrypt(e.encryptedPassword, d, n) << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No entry found for website: " << website << endl;
        }
    }

private:
    vector<Entry> entries;
    long long e, d, n;
};

int main() {
    string accessPassword;
    const string correctPassword = "Tanmay12345";
    cout << "Enter access password: ";
    getline(cin, accessPassword);
    if (accessPassword != correctPassword) {
        cout << "Access denied. Exiting..." << endl;
        return 1;
    }

    PasswordManager manager;
    int choice;
    string site, user, pass, filename = "vault_rsa.dat";

    manager.loadFromFile(filename);

    while (true) {
        cout << "\n1. Add Entry\n2. List Entries\n3. Search by Website\n4. Save and Exit\nChoose an option: ";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            cout << "Website: "; getline(cin, site);
            cout << "Username: "; getline(cin, user);
            cout << "Password: "; getline(cin, pass);
            manager.addEntry(site, user, pass);
        } else if (choice == 2) {
            manager.listEntries();
        } else if (choice == 3) {
            cout << "Enter website to search: ";
            getline(cin, site);
            manager.getEntryByWebsite(site);
        } else if (choice == 4) {
            manager.saveToFile(filename);
            break;
        } else {
            cout << "Invalid option." << endl;
        }
    }
    return 0;
}
