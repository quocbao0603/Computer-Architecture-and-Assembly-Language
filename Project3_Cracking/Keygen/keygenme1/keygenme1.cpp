#include <cstdio>
#include <lmcons.h>
#include <iostream>
#include <Windows.h>
#define INFO_BUFFER_SIZE 32767


using namespace std;


int ROL16(int c) {
    // roll left 16 bit so 4 byte
    int r = 0;
    for (int i = 31; i >= 16; --i) {
        int bit = c >> (i - 16) & 1;
        r += bit * (1 << i);
    }
    int ptr = 31;
    for (int i = 15; i >= 0; --i) {
        int bit = c >> ptr & 1;
        ptr--;
        r += bit * (1 << i);
    }
    return r;
}

char ROR4(char c) {
    // roll right 16 bit so 1 byte
    int r = 0;
    for (int i = 7 - 4; i >= 0; --i) {
        int bit = c >> (i + 4) & 1;
        r += bit * (1 << i);
    }
    int ptr = 3;
    for (int i = 7; i > 7 - 4; --i) {
        int bit = c >> ptr & 1;
        ptr--;
        r += bit * (1 << i);
    }
    return r;
}

int _byteswap_ulong (int val ){
    int res = 0;
    for (int i = 0; i < 4; i++){
        res = res | (val & 255);
        val >>= 8;
        if (i < 3) res <<= 8;
    }
    return res;
}

int ROR16(int c) {
    // roll right 16 bit so 4 byte
    int r = 0;
    for (int i = 31 - 16; i >= 0; --i) {
        int bit = c >> (i + 16) & 1;
        r += bit * (1 << i);
    }
    int ptr = 15;
    for (int i = 31; i > 31 - 16; --i) {
        int bit = c >> ptr & 1;
        ptr--;
        r += bit * (1 << i);
    }
    return r;
}

unsigned int fake_ID(string s) {
    int v1 = 0, v2 = 0, v4 = 0, v5, v6;
    unsigned int v3 = 0;
    for (int i = 0; i < s.size(); i += 2) {
        char p = s[i], q = i + 1 < s.size() ? s[i + 1] : 0;
     //   swap(p, q);
        v2 = (v2 & 0xFFFFFF00) + (0x000000FF & (~q));
        v1 = (v1 & 0xFFFFFF00) + (0x000000FF & (v2 + ROR4(p)));
        v5 = v1 * v2;
        v4 += v5;
        v6 = v1 + v3;
        v3 = v5;
        v2 = v6;
    }
    return v4 + _byteswap_ulong(v3);
}

int main() {
    //Get computername
    TCHAR  computername[INFO_BUFFER_SIZE];
    DWORD  computername_len = INFO_BUFFER_SIZE + 1;
    GetComputerName( (TCHAR*)computername, &computername_len );
    wcout << "Computer Name: " << computername << endl;
    string name = "KhoaDucBao";
    int v3 = 0, v4 = 0;
    int v5 = 0x7FFF;
    int ID = 2842248294;

    for (int i = 0; i < name.size(); ++i) {
        // get 2 byte lien tiep
        int p = name[i], q = i + 1 < name.size() ? name[i + 1] : 0;
        int x = (q << 8) + p;

        v3 = (v3 & 0xFFFF0000) + (0x0000FFFF & x); // LOWORD

        v3 = ((ID & 0xF8F800 ^ (v3 << 8)) + 7106412) ^ 0x10101010;
        v4 += v3;
        v5 = (ID & 0xF8F800) + 8 * (v3 + v5 - 2964781);
    }
    int v6 = 16;
    int v7 = 0;
    int v8 = 0;
    while (v6) {
        v7 = ROL16(_byteswap_ulong(v5 + v7));
        v8 = ROR16(_byteswap_ulong(v4 + v8));
        --v6;
    }
    // v10, v9, v7, v8
    //cout << "EDI, ESI, ECX, EDX: " << v5 << " " << v4 << " " << v7 << " " << v8 << endl;
    // %08x-%08x-%08x-%08x
    char buffer[50];
    int n = sprintf(buffer, "%08X-%08X-%08X-%08X", v5, v4, v7, v8);
    cout << "ID:     " << fake_ID((string) computername) << "\n";
    cout << "Name:   " << name << "\n";
    printf("Serial: %s\n", buffer);

    return 0;
}
