#include <bits/stdc++.h>

using namespace std;

char ROL3(char c) {
    char r = 0;
    for (int i = 7; i >= 3; --i) {
        int bit = c >> (i - 3) & 1;
        r += bit * (1 << i);
    }

    int ptr = 7;
    for (int i = 2; i >= 0; --i) {
        int bit = c >> ptr & 1;
        ptr--;
        r += bit * (1 << i);
    }
    return r;
}

string get_seed(string name, string rotate_string) {
    int len = rotate_string.size();
    string res = "";
    int v6 = ROL3(name[0]); // rol 3 bit ky tu dau tien
    for (int i = 0; i < name.size(); ++i) {
        char pre_char = name[i];
        char cur_char = i + 1 < name.size() ? name[i + 1] : 0;
        int temp = (v6 + (cur_char ^ pre_char)) & 0xFF;
        v6 = (v6 + temp) & 0xFF;
        res.push_back(rotate_string[temp % len]);
    }
    return res;
}

int find_char(char c, string rot) {
    for (int i = 0; i < rot.size(); ++i) if (rot[i] == c) return i;
    return -1;
}

string Rot(string s, int n) {
    string r = s.substr(0, n);
    return s.substr(n, s.size() - n) + r;
}

string Rotate(string s, int n) {
    n *= 4;
    if (n > 60) n = 30;
    string r = s.substr(0, n);
    return s.substr(n, s.size() - n) + r;
}

string con = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

void chk(char char_seed, char char_name, string rot_string) {
    // can tim char_ser = char_name
    int idx = find_char(char_seed, rot_string);
    int need_idx = find_char(char_name, rot_string);
    string rot2 = Rot(rot_string, idx);
    cout << rot2[need_idx];
}

string RemoveSpecialChar(string name) {
    string res = "";
    for (char c: name) if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) res += c;
    return res;
}

int main() {
    string name;
    cout << "Nhap name: ";
    cin >> name;
    name = RemoveSpecialChar(name);
    string t = Rotate(con, name.size());
    string seed = get_seed(name, t);
    cout << "Name: " << name << '\n';
    cout << "Rotate string: " << t << endl;
    cout << "Seed: " << seed << endl;
    cout << "Serial: ";
    for (int i = 0; i < name.size(); ++i) {
        chk(seed[i], name[i], t);
    }
    return 0;
}
